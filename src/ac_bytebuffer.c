// Public domain (PD)

#include "ac_bytebuffer.h"

BYTEBUFFER *BB_Create(UI64 len, UI8 val) {
	// Initialize structure
	BYTEBUFFER *temp = malloc(sizeof(BYTEBUFFER));
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

BYTEBUFFER *BB_FromPtr(UI8 *ptr, UI64 len) {
	if (!ptr || !len) { return NULL; }
	// Initialize BYTEBUFFER structure
	BYTEBUFFER *temp = malloc(sizeof(BYTEBUFFER));
	if (!temp) { return NULL; }
	temp->len = len; temp->cap = 1;
	while (temp->cap < temp->len) { temp->cap <<= 1; }
	// Alloc data and copy over
	temp->data = malloc(UI8_SIZE * temp->cap);
	if (!temp->data) { free(temp); return NULL; }
	memcpy(temp->data, ptr, UI8_SIZE * len);
	return temp;
}

CHAR *BB_ToString(BYTEBUFFER *bb) {
	if (!bb || !bb->data) { return NULL; }
	UI64 limit = 0;
	while (limit < bb->len) {
		if (!bb->data[limit]) { break; }
		++limit;
	}
	CHAR *temp = malloc(CHAR_SIZE * (limit + 1));
	memcpy(temp, bb->data, UI8_SIZE * limit);
	temp[limit] = '\0'; return temp;
}

BYTEBUFFER *BB_FromFile(CHAR *path, UI8 mode) {
	// Initialize file handle and structure
	if (!path) { return NULL; }
	FILE *file = fopen(path, mode == BB_MODE_BIN ? "rb" : "r");
	if (!file) { return NULL; }
	BYTEBUFFER *temp = malloc(sizeof(BYTEBUFFER));
	if (!temp) { fclose(file); return NULL; }
	temp->len = 0; temp->cap = 1;
	// Read file, don't alloc if length is zero
	while (fgetc(file) != EOF) {
		if (++temp->len == UI64_MAX) { break; }
	}
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

BOOLEAN BB_ToFile(BYTEBUFFER *bb, CHAR *path, BOOLEAN append, UI8 mode) {
	// Initialize file handle, write/append and bin/txt based on parameters
	if (!bb || !bb->data || !path) { return FALSE; }
	static CHAR const *FMODES[4] = {"wb", "w", "ab", "a"};
	FILE *file = fopen(path, FMODES[(append << 1) & (mode & 1)]);
	if (!file) { return FALSE; }
	// Write to file
	for (UI64 i = 0; i < bb->len; ++i) {
		fputc(bb->data[i], file);
	}
	fclose(file); return TRUE;
}

BOOLEAN BB_Push(BYTEBUFFER *bb, UI8 val) {
	if (!bb || bb->len == UI64_MAX) { return FALSE; }
	// If size is zero, use malloc, otherwise use realloc
	if (!bb->len && !bb->data) {
		if (!(bb->data = malloc(UI8_SIZE))) { return FALSE; }
	} else if (bb->len == bb->cap) {
		bb->data = realloc(bb->data, UI8_SIZE * (bb->cap <<= 1));
		if (!bb->data) { return FALSE; }
	}
	bb->data[bb->len++] = val; return TRUE;
}

UI8 BB_Pop(BYTEBUFFER *bb) {
	if (!bb || !bb->data || !bb->len) { return 0; }
	// Subtract size and save value into temp then resize if necessary
	UI8 temp = bb->data[--bb->len];
	if (bb->len == bb->cap) {
		bb->data = realloc(bb->data, UI8_SIZE * (bb->cap >>= 1));
	}
	return temp;
}

UI64 BB_FirstOf(BYTEBUFFER *bb, UI8 val) {
	if (!bb || !bb->data || !bb->len) { return UI64_MAX; }
	// Loop until match found, if not found then return error
	for (UI64 i = 0; i < bb->len; ++i) {
		if (bb->data[i] == val) { return val; }
	}
	return UI64_MAX;
}

UI64 BB_LastOf(BYTEBUFFER *bb, UI8 val) {
	if (!bb || !bb->data || !bb->len) { return UI64_MAX; }
	// Loop until match found, if not found then return error
	for (UI64 i = bb->len; --i < bb->len;) {
		if (bb->data[i] == val) { return val; }
	}
	return UI64_MAX;
}

BOOLEAN BB_Copy(BYTEBUFFER *dst, BYTEBUFFER *src) {
	if (!src || !src->data) { return FALSE; }
	// If dst is NULL, alloc
	if (!dst && !(dst = malloc(sizeof(BYTEBUFFER)))) {
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

BOOLEAN BB_Concat(BYTEBUFFER *dst, BYTEBUFFER *src) {
	if (!dst || !dst->data || !src || !src->data) { return FALSE; }
	// For loop to push data to destination
	for (UI64 i = 0; i < src->len; ++i) {
		BB_Push(dst, BB_Get(src, i));
	}
	return TRUE;
}

SI8 BB_Compare(BYTEBUFFER *bb0, BYTEBUFFER *bb1) {
	if (!bb0 || !bb1 || !bb0->data || !bb1->data) { return SI8_MIN; }
	UI64 limit = fmin(bb0->len, bb1->len);
	for (UI64 i = 0; i < limit; ++i) {
		if (bb0->data[i] < bb1->data[i]) { return -1; }
		else if (bb0->data[i] > bb1->data[i]) { return 1; }
	}
	return bb0->len < bb1->len ? -1 : bb0->len > bb1->len;
}

VOID BB_PrintBin(BYTEBUFFER *bb) {
	if (!bb || !bb->data) { return; }
	// For loop to print values
	for (UI64 i = 0; i < bb->len; ++i) {
		if (i && !(i & 0xF)) { putchar('\n'); }
		printf("%02X ", bb->data[i]);
	}
}

VOID BB_PrintTxt(BYTEBUFFER *bb) {
	if (!bb || !bb->data) { return; }
	// For loop to print values
	for (UI64 i = 0; (i < bb->len) && bb->data[i]; ++i) {
		putchar(bb->data[i]);
	}
}