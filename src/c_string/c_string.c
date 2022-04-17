#include "c_string.h"
#include "errno.h"
#include <string.h>

CString 
string_new(const char* string)
{
    CString new_string = NULL;
    size_t len = strlen(string);
    new_string = (char *) malloc(sizeof(char) * len);
    if (new_string == NULL) {
        free(new_string);
        errno = ENOMEM;
        return NULL;
    }
    memcpy(new_string, string, len);
    return new_string;
}

int
string_insert(CString string, size_t pos, const char character)
{
    size_t len = strlen(string);
    if (pos > len) {
        errno = ENOMEM;
        return -1;
    }
    char* new_string = (char *)realloc(string, len);
    if (new_string == NULL) {
        errno = ENOMEM;
        return -1;
    }   

    char* temp = (char*) malloc(sizeof(char) * len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }

    memcpy(temp, new_string + pos, len - pos);
    new_string[pos] = character;
    memcpy(new_string + pos + 1, temp, len - pos);
    string = new_string;

    if (temp != NULL)
        free(temp);
    return 0;
}

int
string_insert_str(CString string, size_t pos, const char* ins_str)
{
    size_t len = strlen(string);
    if (pos > len) {
        errno = ENOMEM;
        return -1;
    }
    size_t ins_str_len = strlen(ins_str);
    char* new_string = (char *)realloc(string, len + ins_str_len);
    if (new_string == NULL) {
        errno = ENOMEM;
        return -1;
    }

    char* temp = (char*) malloc(sizeof(char) * len - pos);
    if (temp == NULL) {
        errno = ENOMEM;
        return -1;
    }
    memcpy(temp, new_string + pos, len - pos);
    memcpy(new_string + pos, ins_str, ins_str_len);
    memcpy(new_string + pos + ins_str_len, temp, len - pos);
    string = new_string;

    if (temp != NULL)
        free(temp);
    return 0;
}

int
string_delete(CString string)
{
    free(string);
    string = NULL;
    return 0;
}
