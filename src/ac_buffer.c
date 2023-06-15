// Public domain (PD)

#include "ac_buffer.h"

BUFFER *BUF_Create(UI64 len, UI8 val) {
	// Initialize structure
	BUFFER *temp = malloc(sizeof(BUFFER));
	if (!temp) { return NULL; }
	temp->len = len; temp->cap = 1;
	// If length is zero, set data to NULL
	if (!len) { temp->data = NULL; return temp; }
	// Otherwise, alloc to capacity and set
	while (temp->cap < len) { temp->cap <<= 1; }
	temp->data = malloc(UI8_SIZE * temp->cap);
	if (!temp->data) { free(temp); return NULL; }
	memset(temp->data, val, UI8_SIZE * len);
	return temp;
}

BUFFER *BUF_FromPointer(UI8 *ptr, UI64 len) {
	if (!ptr || !len) { return NULL; }
	// Initialize BUFFER structure
	BUFFER *temp = malloc(sizeof(BUFFER));
	if (!temp) { return NULL; }
	temp->len = len; temp->cap = 1;
	while (temp->cap < temp->len) { temp->cap <<= 1; }
	// Alloc data and copy over
	temp->data = malloc(UI8_SIZE * temp->cap);
	if (!temp->data) { free(temp); return NULL; }
	memcpy(temp->data, ptr, UI8_SIZE * len);
	return temp;
}

BUFFER *BUF_FromString(CHAR *str) {
	UI64 len;
	if (!str || !(len = strlen(str))) { return NULL; }
	// Initialize BUFFER structure
	BUFFER *temp = malloc(sizeof(BUFFER));
	if (!temp) { return NULL; }
	temp->len = len; temp->cap = 1;
	while (temp->cap < temp->len) { temp->cap <<= 1; }
	// Alloc data and copy over
	temp->data = malloc(UI8_SIZE * temp->cap);
	if (!temp->data) { free(temp); return NULL; }
	memcpy(temp->data, str, UI8_SIZE * len);
	return temp;
}

BUFFER *BUF_FromFile(CHAR *path, BOOLEAN text) {
	// Initialize file handle and structure
	if (!path) { return NULL; }
	FILE *file = fopen(path, !text ? "rb" : "r");
	if (!file) { return NULL; }
	BUFFER *temp = malloc(sizeof(BUFFER));
	if (!temp) { fclose(file); return NULL; }
	// Get length, don't alloc if length is zero
	temp->len = 0; temp->cap = 1;
	while (fgetc(file) != EOF) { ++temp->len; }
	if (!temp->len) { temp->data = NULL; return temp; }
	// Otherwise, alloc to capacity
	while (temp->cap < temp->len) { temp->cap <<= 1; }
	temp->data = malloc(UI8_SIZE * temp->cap);
	if (!temp->data) { free(temp); fclose(file); return NULL; }
	// Reset file position and re-read
	fseek(file, 0, SEEK_SET);
	for (UI64 i = 0; i < temp->len; ++i) {
		temp->data[i] = fgetc(file);
	}
	fclose(file); return temp;
}

UI8 *BUF_ToPointer(BUFFER *buf) {
	if (!buf || !buf->data) { return NULL; }
	// Alloc and set
	UI8 *temp = malloc(UI8_SIZE * buf->len);
	memcpy(temp, buf->data, UI8_SIZE * buf->len);
	return temp;
}

CHAR *BUF_ToString(BUFFER *buf) {
	if (!buf || !buf->data) { return NULL; }
	// Get limit of string length
	UI64 limit = 0;
	while (limit < buf->len) {
		if (!buf->data[limit]) { break; }
		++limit;
	}
	// Alloc and set
	CHAR *temp = malloc(CHAR_SIZE * (limit + 1));
	memcpy(temp, buf->data, UI8_SIZE * limit);
	temp[limit] = '\0'; return temp;
}

BOOLEAN BUF_ToFile(BUFFER *buf, CHAR *path, BOOLEAN append) {
	// Initialize file handle, choose between write/append mode
	if (!buf || !buf->data || !path) { return FALSE; }
	FILE *file = fopen(path, !append ? "wb" : "ab");
	if (!file) { return FALSE; }
	// Write to file
	for (UI64 i = 0; i < buf->len; ++i) {
		fputc(buf->data[i], file);
	}
	fclose(file); return TRUE;
}

// If zero, malloc; if equal to capacity, realloc; otherwise do nothing
static inline BOOLEAN BUF_ResizeUp(BUFFER *buf) {
	if (!buf->len) {
		if (!(buf->data = malloc(UI8_SIZE))) { return FALSE; }
	} else if (buf->len == buf->cap) {
		buf->data = realloc(buf->data, UI8_SIZE * (buf->cap <<= 1));
		if (!buf->data) { return FALSE; }
	}
	return TRUE;
}

// If zero, free; if equal to half-cap, realloc, otherwise do nothing
static inline BOOLEAN BUF_ResizeDown(BUFFER *buf) {
	if (!buf->len) {
		free(buf->data); buf->data = NULL;
	} else if (buf->len == (buf->cap >> 1)) {
		buf->data = realloc(buf->data, UI8_SIZE * (buf->cap >>= 1));
		if (!buf->data) { return FALSE; }
	}
	return TRUE;
}

BOOLEAN BUF_Push(BUFFER *buf, UI8 val) {
	if (!buf || buf->len == UI64_MAX) { return FALSE; }
	// Attempt resize then set value and increase len
	if (!BUF_ResizeUp(buf)) { return FALSE; }
	buf->data[buf->len++] = val; return TRUE;
}

UI8 BUF_Pop(BUFFER *buf) {
	if (!buf || !buf->data || !buf->len) { return 0; }
	// Reduce len and save value then attempt resize
	UI8 temp = buf->data[--buf->len];
	return !BUF_ResizeDown(buf) ? 0 : temp;
}

BOOLEAN BUF_Unshift(BUFFER *buf, UI8 val) {
	if (!buf || buf->len == UI64_MAX) { return FALSE; }
	// Attempt resize then shuffle over
	if (!BUF_ResizeUp(buf)) { return FALSE; }
	memmove(buf->data + 1, buf->data, buf->len++);
	*(buf->data) = val; return TRUE;
}

UI8 BUF_Shift(BUFFER *buf) {
	if (!buf || !buf->data || !buf->len) { return 0; }
	// Save value and reduce len then attempt resize
	UI8 temp = *(buf->data); --buf->len;
	if (!BUF_ResizeDown(buf)) { return 0; }
	// Shuffle over and return
	memmove(buf->data, buf->data + 1, buf->len);
	return temp;
}

BOOLEAN BUF_Insert(BUFFER *buf, UI64 ind, UI8 val) {
	if (!buf || buf->len == UI64_MAX || ind > buf->len) { return FALSE; }
	// Attempt resize then shuffle over and set value
	if (!BUF_ResizeUp(buf)) { return FALSE; }
	UI8 *ptr = buf->data + ind; UI64 movcnt = buf->len++ - ind;
	if (movcnt) { memmove(ptr + 1, ptr, movcnt); }
	*ptr = val; return TRUE;
}

UI8 BUF_Remove(BUFFER *buf, UI64 ind) {
	if (!buf || !buf->data || !buf->len || ind >= buf->len) { return 0; }
	// Get value and shuffle over then attempt resize
	UI8 *ptr = buf->data + ind, temp = *ptr;
	UI64 movcnt = --buf->len - ind;
	if (movcnt) { memmove(ptr, ptr + 1, movcnt); }
	return !BUF_ResizeDown(buf) ? 0 : temp;
}

BOOLEAN BUF_Copy(BUFFER *dst, BUFFER *src) {
	if (!src || !src->data) { return FALSE; }
	// If dst is NULL, alloc
	if (!dst && !(dst = malloc(sizeof(BUFFER)))) {
		return FALSE;
	}
	// If length is zero, use malloc, otherwise realloc
	if (!dst->data) {
		dst->data = malloc(UI8_SIZE * src->cap);
	} else {
		dst->data = realloc(dst->data, UI8_SIZE * src->cap);
	}
	if (!dst->data) { return FALSE; }
	// Copy over len and cap with assignment, memcpy for data
	dst->len = src->len; dst->cap = src->cap;
	memcpy(dst->data, src->data, UI8_SIZE * dst->len);
	return TRUE;
}

BOOLEAN BUF_Concat(BUFFER *dst, BUFFER *src) {
	if (!dst || !src || !src->data) { return FALSE; }
	// For loop to push data to destination
	for (UI64 i = 0; i < src->len; ++i) {
		BUF_Push(dst, BUF_Get(src, i));
	}
	return TRUE;
}

SI8 BUF_Compare(BUFFER *buf0, BUFFER *buf1) {
	if (!buf0 || !buf1 || !buf0->data || !buf1->data) { return SI8_MIN; }
	UI64 limit = MIN(buf0->len, buf1->len);
	for (UI64 i = 0; i < limit; ++i) {
		if (buf0->data[i] < buf1->data[i]) { return -1; }
		else if (buf0->data[i] > buf1->data[i]) { return 1; }
	}
	return buf0->len < buf1->len ? -1 : buf0->len > buf1->len;
}

VOID BUF_PrintBin(BUFFER *buf) {
	if (!buf || !buf->data) { return; }
	// For loop to print values
	for (UI64 i = 0; i < buf->len; ++i) {
		if (i && !(i & 0xF)) { putchar('\n'); }
		printf("%02X ", buf->data[i]);
	}
}

VOID BUF_PrintTxt(BUFFER *buf) {
	if (!buf || !buf->data) { return; }
	// For loop to print values
	for (UI64 i = 0; (i < buf->len) && buf->data[i]; ++i) {
		putchar(buf->data[i]);
	}
}