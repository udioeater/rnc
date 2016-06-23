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

static int shrink_rule(char *dst, char rule, int repeats)
{
    int dstlen = strlen(dst);
    char tmp[dstlen];
    tmp[0] = 0;

    char search[repeats];
    int i;
    for(i = 0; i < repeats; i++) {
        search[i] = rule;
    }

    char *idx = index(dst, rule);
    if (NULL != idx && 0 == strncmp(idx, search, repeats)) {
        char *replace_with = index(ORDER, rule) - 1;
        strncat(tmp, replace_with, 1);
        strcat(tmp, idx+repeats);
        strcpy(dst+(idx-dst), tmp);
        dstlen -= repeats;
        dstlen++;
    }

    return dstlen;
}

static int shrink(char *dst, int dstlen)
{
    shrink_rule(dst, 'I', 5);
    shrink_rule(dst, 'V', 2);
    shrink_rule(dst, 'X', 5);
    shrink_rule(dst, 'L', 2);
    shrink_rule(dst, 'C', 5);
    return shrink_rule(dst, 'D', 2);
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
