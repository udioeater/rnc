#include "rnc.h"
#include <string.h>

static const char ORDER[7] = "MDCLXVI";

static int combine(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
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

    return dstlen;
}

static int shrink(char *dst, int dstlen)
{
    char tmp[dstlen];
    tmp[0] = 0;
    int tmplen = 0;
    int i = 0;

    for (i = 0; i < dstlen; i++) {
        if (0 == strncmp(dst+i, "DD", 2)) {
            strncat(tmp, "M", 1);
            tmplen++;
            i++;
        } else if (0 == strncmp(dst+i, "CCCCC", 5)) {
            strncat(tmp, "D", 1);
            tmplen++;
            i+=4;
        } else if (0 == strncmp(dst+i, "LL", 2)) {
            strncat(tmp, "C", 1);
            tmplen++;
            i++;
        } else if (0 == strncmp(dst+i, "XXXXX", 5)) {
            strncat(tmp, "L", 1);
            tmplen++;
            i+=4;
        } else if (0 == strncmp(dst+i, "VV", 2)) {
            strncat(tmp, "X", 1);
            tmplen++;
            i++;
        } else if (0 == strncmp(dst+i, "IIIII", 5)) {
            strncat(tmp, "V", 1);
            tmplen++;
            i+=4;
        } else {
            strncat(tmp, dst+i, 1);
            tmplen++;
        }
    }
    strncpy(dst, tmp, dstlen);

    return tmplen;
}

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    int dstlen = combine(first, flen, second, slen, dst, maxlen);
    dstlen = shrink(dst, dstlen);

    if (0 == strncmp(dst+dstlen-5, "VIIII", 5)) {
        strncpy(dst+dstlen-5, "IX", 5);
        dstlen -= 3;
    } else if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        strncpy(dst+dstlen-4, "IV", 4);
        dstlen -= 2;
    }
}
