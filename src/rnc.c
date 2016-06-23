#include "rnc.h"
#include <string.h>

static const char ORDER[7] = "MDCLXVI";

static void combine(const char *first, const char *second, char *dst, int maxlen)
{
    *dst = 0;
    int flen = strlen(first);
    int slen = strlen(second);
    int i = 0;
    int j = 0;

    while (strlen(dst) <= (flen + slen - 1)) {
        char *fidx = index(ORDER, *(first+i));
        char *sidx = index(ORDER, *(second+j));

        if (NULL == sidx || (fidx < sidx)) {
            strncat(dst, first+i, 1);
            i++;
        } else {
            strncat(dst, second+j, 1);
            j++;
        }
    }
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

static int shrink(char *dst)
{
    shrink_rule(dst, 'I', 5);
    shrink_rule(dst, 'V', 2);
    shrink_rule(dst, 'X', 5);
    shrink_rule(dst, 'L', 2);
    shrink_rule(dst, 'C', 5);
    return shrink_rule(dst, 'D', 2);
}

static int expand(const char *num, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;
    int len = strlen(num);
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

void add(const char *first, const char *second, char *dst, int maxlen)
{
    int flen = strlen(first);
    char ftmp[flen*3];
    expand(first, ftmp, flen*3);

    int slen = strlen(second);
    char stmp[slen*3];
    expand(second, stmp, slen*3);

    combine(ftmp, stmp, dst, maxlen);
    int dstlen = shrink(dst);

    if (0 == strcmp(dst, "XXXX")) {
        strncpy(dst+dstlen-4, "XL", 4);
        dstlen -= 2;
    } else if (0 == strncmp(dst+dstlen-5, "VIIII", 5)) {
        strncpy(dst+dstlen-5, "IX", 5);
        dstlen -= 3;
    } else if (0 == strncmp(dst+dstlen-4, "IIII", 4)) {
        strncpy(dst+dstlen-4, "IV", 4);
        dstlen -= 2;
    }
}
