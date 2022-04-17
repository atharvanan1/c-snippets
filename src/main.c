#include <stdio.h>
#include "c_string/c_string.h"
#include "Config.h"

int main(void)
{
    CString* test_string = string_new(TEST_STRING);
    string_insert(test_string, 4, 'M');
    string_insert(test_string, 5, 'e');
    string_insert_str(test_string, 6, "NOW!");
    printf("%s\n", test_string->string_data);
    string_delete(test_string);
    return 0;
}