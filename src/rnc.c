#include "rnc.h"
#include <string.h>

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    *dst = 0;
    strncat(dst, first, flen);
    strncat(dst, second, slen);

    if (0 == strncmp(dst, "IIII", 4)) {
        strncpy(dst, "IV", maxlen);
    }
}
