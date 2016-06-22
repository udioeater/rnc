#include "rnc.h"
#include <string.h>

static const char ORDER[7] = "MDCLXVI";

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;
    int i = 0;
    int j = 0;

    while (dstlen <= (flen + slen - 1)) {

        char *fidx = index(ORDER, *(first+i));
        char *sidx = index(ORDER, *(second+j));

        if (NULL == sidx || (fidx < sidx)) {
            strncat(dst, first+i, 1);
            i++;
        } else {
            strncat(dst, second+j, 1);
            j++;
        }

        dstlen++;
    }

    if (0 == strncmp(dst, "VV", 2)) {
        strncpy(dst, "X", 2);
        dstlen--;
    } else if (0 == strncmp(dst, "IIIII", 5)) {
        strncpy(dst, "V", 5);
        dstlen -= 4;
    }

    if (0 == strncmp(dst+dstlen-5, "VIIII", 5)) {
        strncpy(dst+dstlen-5, "IX", 5);
        dstlen -= 3;
    } else if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        strncpy(dst+dstlen-4, "IV", 4);
        dstlen -= 2;
    }
}
