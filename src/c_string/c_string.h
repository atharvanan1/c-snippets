#ifndef C_STRING_H_
#define C_STRING_H_

#include <stdlib.h>

typedef struct c_string {
    char *string_data;
    size_t size;
} CString;

CString* string_new(const char* string);
int string_insert(CString* string, size_t pos, const char character);
int string_insert_str(CString* string, size_t pos, char* ins_str);
int string_delete(CString* string);

#endif /* C_STRING_H_ */
