#include "rnc.h"
#include <string.h>

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;

    strncat(dst, first, flen);
    dstlen += flen;

    strncat(dst, second, slen);
    dstlen += slen;

    if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        char *idx = index(dst, 'I');
        strncpy(dst+(idx - dst), "IV", 4);
        dstlen -= 2;
    }
}
