#include "c_string.h"
#include <errno.h>
#include <string.h>

/*
 * string_new
 *
 * string: char buffer from which
 *
 * creates and return CString from given
 * character buffer
 *
 * Returns: CString
 */
CString 
string_new(const char* string)
{
    CString new_string = NULL;
    size_t alloc_len = strlen(string) + 1;     // As strlen returns length without '\0'
    new_string = (char *) malloc(sizeof(char) * alloc_len);
    if (new_string == NULL) {
        free(new_string);
        errno = ENOMEM;
        return NULL;
    }
    strcpy(new_string, string);
    return new_string;
}

/*
 * string_insert
 *
 * string_ptr: pointer to the CString type
 * pos: 0-indexed position
 * character: character to insert
 *
 * inserts a single character at given position
 * Ex. "Test", 0, 'K' -> "KTest"
 * Ex. "Test", 4, 'K' -> "TestK"
 *
 * sending out of bound position will return -1
 *
 * Returns: 0 when successful, -1 when error
 * errno will be set on error
 */
int
string_insert(CString* string_ptr, size_t pos, const char character)
{
    size_t alloc_len = strlen(*string_ptr) + 1;     // As strlen returns length without '\0'
    if (pos > alloc_len) {
        errno = EINVAL;
        return -1;
    }
    CString new_string = (CString) realloc(*string_ptr, alloc_len + 1);
    if (new_string == NULL) {
        errno = ENOMEM;
        return -1;
    }

    char* temp = (char*) malloc(sizeof(char) * alloc_len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }

    strcpy(temp, new_string + pos);
    new_string[pos] = character;
    strcpy(new_string + pos + 1, temp);
    *string_ptr = new_string;

    if (temp != NULL)
        free(temp);
    return 0;
}

/*
 * string_insert
 *
 * string_ptr: pointer to the CString type
 * pos: 0-indexed position
 * ins_str: character buffer to copy
 *
 * inserts a single character at given position
 * Ex. "Test", 0, 'Me' -> "MeTest"
 * Ex. "Test", 4, 'Me' -> "TestMe"
 *
 * sending out of bound position will return -1
 *
 * Returns: 0 when successful, -1 when error
 * errno will be set on error
 */
int
string_insert_str(CString* string_ptr, size_t pos, const char* ins_str)
{
    size_t alloc_len = strlen(*string_ptr) + 1;      // As strlen returns length without '\0'
    if (pos > alloc_len) {
        errno = ENOMEM;
        return -1;
    }
    size_t ins_str_len = strlen(ins_str);    // We don't need null character from here
    CString new_string = (CString) realloc(*string_ptr, alloc_len + ins_str_len);
    if (new_string == NULL) {
        errno = ENOMEM;
        return -1;
    }

    char* temp = (char*) malloc(sizeof(char) * alloc_len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }
    strcpy(temp, new_string + pos);
    strcpy(new_string + pos, ins_str);
    strcpy(new_string + pos + ins_str_len, temp);
    *string_ptr = new_string;

    free(temp);
    return 0;
}

/*
 * string_delete
 *
 * string: CString type
 *
 * deletes the CString type
 *
 * Returns: int
 */
int
string_delete(CString string)
{
    free(string);
    string = NULL;
    return 0;
}
