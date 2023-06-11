// Public domain (PD)

#ifndef _AC_BYTEBUFFER_H_
#define _AC_BYTEBUFFER_H_

#include "ac_types.h"

#define BB_MODE_BIN 0
#define BB_MODE_TXT 1

typedef struct {
	UI8 *data; UI64 len, cap;
} BYTEBUFFER;

// Creates a BYTEBUFFER.
// \param len The length to initalize to.
// \param val The value to fill in. If len is 0, then ignore this.
// \return A BYTEBUFFER on success, NULL on failure.
extern BYTEBUFFER *BB_Create(UI64 len, UI8 val);

// Creates a BYTEBUFFER from a pointer.
// \param ptr The pointer to get the data from.
// \param len The amount of bytes to retrieve.
// \return A BYTEBUFFER on success, NULL on failure.
extern BYTEBUFFER *BB_FromPtr(UI8 *ptr, UI64 len);

// Converts a BYTEBUFFER to a usable string.
// \param bb The source BYTEBUFFER to use.
// \return A string on success, NULL on failure.
extern CHAR *BB_ToString(BYTEBUFFER *bb);

// Creates a BYTEBUFFER from the contents of a file.
// \param path The file to read.
// \param mode The method of reading. Accepted values are: BB_MODE_BIN, BB_MODE_TXT.
// \return A BYTEBUFFER on success, NULL on failure.
extern BYTEBUFFER *BB_FromFile(CHAR *path, UI8 mode);

// Writes to a file using the contents of a BYTEBUFFER.
// \param bb The source BYTEBUFFER to use.
// \param path The file to write to.
// \param append If true, adds to end of pre-existing data. Otherwise, override.
// \param mode The method of writing. Accepted values are: BB_MODE_BIN, BB_MODE_TXT.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BB_ToFile(BYTEBUFFER *bb, CHAR *path, BOOLEAN append, UI8 mode);

// Adds byte to end of BYTEBUFFER.
// \param bb The BYTEBUFFER to operate on.
// \param val The value to push to the BYTEBUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BB_Push(BYTEBUFFER *bb, UI8 val);

// Removes byte from end of BYTEBUFFER.
// \param bb The BYTEBUFFER to operate on.
// \return Returns the previous last value. On failure returns 0.
// \return Be sure to add additional checks where this may happen.
extern UI8 BB_Pop(BYTEBUFFER *bb);

// Gets the first instance of a value in a BYTEBUFFER.
// \param bb The BYTEBUFFER to retrieve from.
// \param val The value to search for.
// \return The matching index, or UI64_MAX on error.
extern UI64 BB_FirstOf(BYTEBUFFER *bb, UI8 val);

// Gets the last instance of a value in a BYTEBUFFER.
// \param bb The BYTEBUFFER to retrieve from.
// \param val The value to search for.
// \return The matching index, or UI64_MAX on error.
extern UI64 BB_LastOf(BYTEBUFFER *bb, UI8 val);

// Copies a BYTEBUFFER from one place to another.
// \param dst The destination BYTEBUFFER.
// \param src The source BYTEBUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BB_Copy(BYTEBUFFER *dst, BYTEBUFFER *src);

// Concatenates one BYTEBUFFER to another.
// \param dst The destination BYTEBUFFER.
// \param src The source BYTEBUFFER.
// \return On success, returns TRUE. Otherwise, returns FALSE.
extern BOOLEAN BB_Concat(BYTEBUFFER *dst, BYTEBUFFER *src);

// Compares the contents of two BYTEBUFFER structures.
// \param bb0 The first BYTEBUFFER to compare.
// \param bb1 The second BYTEBUFFER to compare.
// \return If they are equal in both content and length, returns 0.
// \return If bb0 has a lower value or is shorter, returns -1. Otherwise, returns 1.
extern SI8 BB_Compare(BYTEBUFFER *bb0, BYTEBUFFER *bb1);

// Prints the contents of a BYTEBUFFER in binary format.
// \param bb The BYTEBUFFER to print.
extern VOID BB_PrintBin(BYTEBUFFER *bb);

// Prints the contents of a BYTEBUFFER as a string.
// \param bb The BYTEBUFFER to print.
extern VOID BB_PrintTxt(BYTEBUFFER *bb);

// Sets an element of a BYTEBUFFER.
// \param bb The BYTEBUFFER to operate on.
// \param index The index to set.
// \param val The value to set to.
// \return On success, returns TRUE. Otherwise, returns FALSE.
static inline BOOLEAN BB_Set(BYTEBUFFER *bb, UI64 index, UI8 val) {
	if (!bb || !bb->data || index >= bb->len) { return FALSE; }
	bb->data[index] = val; return TRUE;
}

// Gets an element of a BYTEBUFFER.
// \param bb The BYTEBUFFER to retrieve from.
// \param index The index from which to get.
// \return Returns the value being held at index. On failure returns 0.
// \return Be sure to add additional checks where this may happen.
static inline UI8 BB_Get(BYTEBUFFER *bb, UI64 index) {
	return !bb || !bb->data || index >= bb->len ? 0 : bb->data[index];
}

// Gets the value of the first element of a BYTEBUFFER.
// \param bb The BYTEBUFFER to retrieve from.
// \return Returns the first element of bb. On failure returns 0.
// \return Be sure to add additional checks where this may happen.
static inline UI8 BB_Front(BYTEBUFFER *bb) {
	return !bb || !bb->data ? 0 : *(bb->data);
}

// Gets the value of the last element of a BYTEBUFFER.
// \param bb The BYTEBUFFER to retrieve from.
// \return Returns the last element of bb. On failure returns 0.
// \return Be sure to add additional checks where this may happen.
static inline UI8 BB_Back(BYTEBUFFER *bb) {
	return !bb || !bb->data ? 0 : bb->data[bb->len - 1];
}

// Deletes a BYTEBUFFER
// \param bb The BYTEBUFFER to free.
static inline VOID BB_Delete(BYTEBUFFER *bb) {
	if (!bb) { return; }
	if (bb->data) { free(bb->data); }
	free(bb);
}

#endif