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
    char *idx = index(dst, 'I');
    if (NULL != idx && 0 == strncmp(idx, "IIIII", 5)) {
        strcpy(dst+(idx-dst), "V");
        dstlen -= 4;
    }

    tmp[0] = 0;
    idx = index(dst, 'V');
    if (NULL != idx && 0 == strncmp(idx, "VV", 2)) {
        strcat(tmp, "X");
        strcat(tmp, idx+2);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= 1;
    }

    tmp[0] = 0;
    idx = index(dst, 'X');
    if (NULL != idx && 0 == strncmp(idx, "XXXXX", 5)) {
        strcat(tmp, "L");
        strcat(tmp, idx+5);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= 4;
    }

    tmp[0] = 0;
    idx = index(dst, 'L');
    if (NULL != idx && 0 == strncmp(idx, "LL", 2)) {
        strcat(tmp, "C");
        strcat(tmp, idx+2);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= 1;
    }

    tmp[0] = 0;
    idx = index(dst, 'C');
    if (NULL != idx && 0 == strncmp(idx, "CCCCC", 5)) {
        strcat(tmp, "D");
        strcat(tmp, idx+5);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= 4;
    }

    tmp[0] = 0;
    idx = index(dst, 'D');
    if (NULL != idx && 0 == strncmp(idx, "DD", 2)) {
        strcat(tmp, "M");
        strcat(tmp, idx+2);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= 1;
    }

    return dstlen;
}

static int expand(const char *num, int len, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;
    int i;

    for (i = 0; i < len; i++) {
        if (0 == strncmp(num+i, "XC", 2)) {
            strncat(dst, "LXXXX", 5);
            dstlen += 5;
            i++;
        } else if (0 == strncmp(num+i, "XL", 2)) {
            strncat(dst, "XXXX", 4);
            dstlen += 4;
            i++;
        } else if (0 == strncmp(num+i, "IX", 2)) {
            strncat(dst, "VIIII", 5);
            dstlen += 5;
            i++;
        } else if (0 == strncmp(num+i, "IV", 2)) {
            strncat(dst, "IIII", 4);
            dstlen += 4;
            i++;
        } else {
            strncat(dst, num+i, 1);
            dstlen++;
        }
    }
    return dstlen;
}

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    char ftmp[flen*3];
    flen = expand(first, flen, ftmp, flen*3);

    char stmp[slen*3];
    slen = expand(second, slen, stmp, slen*3);

    int dstlen = combine(ftmp, flen, stmp, slen, dst, maxlen);
    dstlen = shrink(dst, dstlen);

    if (0 == strncmp(dst+dstlen-5, "VIIII", 5)) {
        strncpy(dst+dstlen-5, "IX", 5);
        dstlen -= 3;
    } else if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        strncpy(dst+dstlen-4, "IV", 4);
        dstlen -= 2;
    }
}
