// Public domain (PD)

#ifndef _AC_BUFFER_H_
#define _AC_BUFFER_H_

#include "ac_types.h"
#include "ac_math.h"

typedef struct {
	UI8 *data; UI64 len, cap;
} BUFFER;

// Creates a BUFFER.
// \param len The length to initalize to.
// \param val The value to fill in. If len is 0, then ignore this.
// \return A BUFFER on success, NULL on failure.
extern BUFFER *BUF_Create(UI64 len, UI8 val);

// Creates a BUFFER from a pointer.
// \param ptr The pointer to get the data from.
// \param len The amount of bytes to retrieve.
// \return A BUFFER on success, NULL on failure.
extern BUFFER *BUF_FromPointer(UI8 *ptr, UI64 len);

// Creates a BUFFER from a string.
// \param str The string to get the data from.
// \return A BUFFER on success, NULL on failure.
extern BUFFER *BUF_FromString(CHAR *str);

// Creates a BUFFER from the contents of a file.
// \param path The file to read.
// \return A BUFFER on success, NULL on failure.
extern BUFFER *BUF_FromFile(CHAR *path, BOOLEAN text);

// Converts a BUFFER to an array of bytes.
// \param buf The source BUFFER to use.
// \return A pointer to the data on success, NULL on failure.
extern UI8 *BUF_ToPointer(BUFFER *buf);

// Converts a BUFFER to a usable string.
// \param buf The source BUFFER to use.
// \return A string on success, NULL on failure.
extern CHAR *BUF_ToString(BUFFER *buf);

// Writes to a file using the contents of a BUFFER.
// \param buf The source BUFFER to use.
// \param path The file to write to.
// \param append If true, adds to end of pre-existing data. Otherwise, override.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_ToFile(BUFFER *buf, CHAR *path, BOOLEAN append);

// Adds a byte to the end of a BUFFER.
// \param buf The BUFFER to operate on.
// \param val The value to push to the BUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_Push(BUFFER *buf, UI8 val);

// Removes a byte from the end of a BUFFER.
// \param buf The BUFFER to operate on.
// \return Returns the previous last value. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
extern UI8 BUF_Pop(BUFFER *buf);

// Adds a byte to the beginning of a BUFFER.
// \param buf The BUFFER to operate on.
// \param val The value to add to the BUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_Unshift(BUFFER *buf, UI8 val);

// Removes a byte from the beginning of a BUFFER.
// \param buf The BUFFER to operate on.
// \return Returns the previous first value. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
extern UI8 BUF_Shift(BUFFER *buf);

// Inserts a value into a BUFFER.
// \param buf The BUFFER to operate on.
// \param ind The index to insert into.
// \param val The value to be inserted.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_Insert(BUFFER *buf, UI64 ind, UI8 val);

// Removes byte from a BUFFER.
// \param buf The BUFFER to operate on.
// \param ind The index to retrieve from.
// \return Returns the value located at ind. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
extern UI8 BUF_Remove(BUFFER *buf, UI64 ind);

// Copies a BUFFER from one place to another.
// \param dst The destination BUFFER.
// \param src The source BUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_Copy(BUFFER *dst, BUFFER *src);

// Concatenates one BUFFER to another.
// \param dst The destination BUFFER.
// \param src The source BUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BUF_Concat(BUFFER *dst, BUFFER *src);

// Compares the contents of two BUFFER structures.
// \param buf0 The first BUFFER to compare.
// \param buf1 The second BUFFER to compare.
// \return If they are equal in both content and length, returns 0.
// \return If buf0 has a lower value or is shorter, returns -1.
// \return If buf1 has a lower value or is shorter, returns 1.
// \return On failure returns SI8_MIN.
extern SI8 BUF_Compare(BUFFER *buf0, BUFFER *buf1);

// Prints the contents of a BUFFER in binary format.
// \param buf The BUFFER to print.
extern VOID BUF_PrintBin(BUFFER *buf);

// Prints the contents of a BUFFER as a string.
// \param buf The BUFFER to print.
extern VOID BUF_PrintTxt(BUFFER *buf);

// Gets an element of a BUFFER.
// \param buf The BUFFER to retrieve from.
// \param ind The index from which to get.
// \return Returns the value being held at index. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
static inline UI8 BUF_Get(BUFFER *buf, UI64 ind) {
	return !buf || !buf->data || ind >= buf->len ? 0 : buf->data[ind];
}

// Sets an element of a BUFFER.
// \param buf The BUFFER to operate on.
// \param ind The index to set.
// \param val The value to set to.
// \return On success, returns TRUE. Otherwise, returns FALSE.
static inline BOOLEAN BUF_Set(BUFFER *buf, UI64 ind, UI8 val) {
	if (!buf || !buf->data || ind >= buf->len) { return FALSE; }
	buf->data[ind] = val; return TRUE;
}

// Gets the value of the first element of a BUFFER.
// \param buf The BUFFER to retrieve from.
// \return Returns the first element of buf. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
static inline UI8 BUF_GetFront(BUFFER *buf) {
	return !buf || !buf->data ? 0 : *(buf->data);
}

// Sets the vlaue of the first element of a BUFFER.
// \param buf The BUFFER to operate on.
// \param val The value to set to.
// \return On success, returns TRUE. Otherwise, returns FALSE.
static inline BOOLEAN BUF_SetFront(BUFFER *buf, UI8 val) {
	if (!buf || !buf->data || !buf->len) { return FALSE; }
	*(buf->data) = val; return TRUE;
}

// Gets the value of the last element of a BUFFER.
// \param buf The BUFFER to retrieve from.
// \return Returns the last element of buf. On failure returns 0.
// \note Be sure to add additional checks where failure may occur.
static inline UI8 BUF_GetBack(BUFFER *buf) {
	return !buf || !buf->data ? 0 : buf->data[buf->len - 1];
}

// Sets the vlaue of the last element of a BUFFER.
// \param buf The BUFFER to operate on.
// \param val The value to set to.
// \return On success, returns TRUE. Otherwise, returns FALSE.
static inline BOOLEAN BUF_SetBack(BUFFER *buf, UI8 val) {
	if (!buf || !buf->data || !buf->len) { return FALSE; }
	buf->data[buf->len - 1] = val; return TRUE;
}

// Gets the first instance of a value in a BUFFER.
// \param buf The BUFFER to retrieve from.
// \param val The value to search for.
// \return The matching index, or UI64_MAX on error.
static inline UI64 BUF_First(BUFFER *buf, UI8 val) {
	if (!buf || !buf->data || !buf->len) { return UI64_MAX; }
	// Loop until match found, if not found then return error
	for (UI64 i = 0; i < buf->len; ++i) {
		if (buf->data[i] == val) { return val; }
	}
	return UI64_MAX;
}

// Gets the last instance of a value in a BUFFER.
// \param buf The BUFFER to retrieve from.
// \param val The value to search for.
// \return The matching index, or UI64_MAX on error.
static inline UI64 BUF_Last(BUFFER *buf, UI8 val) {
	if (!buf || !buf->data || !buf->len) { return UI64_MAX; }
	// Loop until match found, if not found then return error
	for (UI64 i = buf->len; --i < buf->len;) {
		if (buf->data[i] == val) { return val; }
	}
	return UI64_MAX;
}

// Deletes a BUFFER
// \param buf The BUFFER to free.
static inline VOID BUF_Delete(BUFFER *buf) {
	if (!buf) { return; }
	if (buf->data) { free(buf->data); }
	free(buf);
}

#endif