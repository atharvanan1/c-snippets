#include "memfunc.h"

#define A 4
#define D int

static int _memcpy_byte(void *dest, void *src, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        *((char *) dest + i) = *((char *) src + i);
    }
}

static int _memcpy_byte_4(void *dest, void *src, size_t count)
{
    int s_count = count / 4;
    for (size_t i = 0; i < s_count; i++)
    {
        *((int *) dest + i) = *((int *) src + i);
    }
}

int my_memcpy(void* dest, void* src, size_t count)
{
    if (count == 0)
        return -1;

    if (count <= 4) {
        _memcpy_byte(dest, src, count);
        return 0;
    } else {
        char unaligned_bytes = ((char) src & 0x03L);
        if (unaligned_bytes) {
            _memcpy_byte(dest, src, unaligned_bytes);
            dest += unaligned_bytes;
            src += unaligned_bytes;
            count -= unaligned_bytes;
        }
        unaligned_bytes = count % 4;
        count -= count % 4;
        _memcpy_byte_4(dest, src, count);
        dest += count;
        src += count;
        count -= count;
        if (unaligned_bytes) {
            _memcpy_byte(dest, src, unaligned_bytes);
        }
    }
}

int my_memmove(void *dest, void *src, size_t count)
{
    void *temp = (void *) malloc(sizeof(char) * count);
    my_memcpy(temp, src, count);
    my_memcpy(dest, temp, count);
    free(temp);
}
