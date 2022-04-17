#include "c_string.h"
#include "errno.h"
#include <string.h>

CString* 
string_new(const char* string)
{
    CString* new_string = (CString*) malloc(sizeof(CString));
    if (new_string == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    size_t len = strlen(string);
    new_string->string_data = (char *) malloc(sizeof(char) * len);
    if (new_string->string_data == NULL) {
        free(new_string);
        errno = ENOMEM;
        return NULL;
    }
    memcpy(new_string->string_data, string, len);
    new_string->size = len;
    return new_string;
}

int
string_insert(CString* string, size_t pos, const char character)
{
    char* string_data = string->string_data;
    size_t len = string->size;
    if (pos > len) {
        return -1;
    }
    char* new_string_data = (char *)realloc(string->string_data, len);
    if (new_string_data == NULL) {
        errno = ENOMEM;
        return -1;
    }
    string->string_data = new_string_data;
    string->size = len + 1;
    char* temp = (char*) malloc(sizeof(char) * len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }

    memcpy(temp, string->string_data + pos, len - pos);
    string->string_data[pos] = character;
    memcpy(string->string_data + pos + 1, temp, len - pos);

    if (temp != NULL)
        free(temp);
    return 0;
}

int
string_insert_str(CString* string, size_t pos, char* ins_str)
{
    char* string_data = string->string_data;
    size_t len = string->size;
    if (pos > len) {
        return -1;
    }
    size_t ins_str_len = strlen(ins_str);
    char* new_string_data = (char *)realloc(string->string_data, len + ins_str_len);
    if (new_string_data == NULL) {
        errno = ENOMEM;
        return -1;
    }

    string->string_data = new_string_data;
    string->size = len + ins_str_len;
    char* temp = (char*) malloc(sizeof(char) * len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }
    memcpy(temp, string->string_data + pos, len - pos);
    memcpy(string->string_data + pos, ins_str, ins_str_len);
    memcpy(string->string_data + pos + ins_str_len, temp, len - pos);

    if (temp != NULL)
        free(temp);
    return 0;
}

int
string_delete(CString* string)
{
    free(string->string_data);
    free(string);
    string = NULL;
    return 0;
}
