#include "rnc.h"
#include <string.h>

static const char ORDER[7] = "MDCLXVI";

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;

    if (index(ORDER, *first) < index(ORDER, *second)) {
        strncat(dst, first, flen);
        dstlen += flen;

        strncat(dst, second, slen);
        dstlen += slen;
    } else {
        strncat(dst, second, slen);
        dstlen += slen;

        strncat(dst, first, flen);
        dstlen += flen;
    }

    if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        char *idx = index(dst, 'I');
        strncpy(dst+(idx - dst), "IV", 4);
        dstlen -= 2;
    }
}
