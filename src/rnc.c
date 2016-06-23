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

static void shrink_rule(char *dst, char rule, int repeats)
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
    }
}

static int shrink(char *dst)
{
    shrink_rule(dst, 'I', 5);
    shrink_rule(dst, 'V', 2);
    shrink_rule(dst, 'X', 5);
    shrink_rule(dst, 'L', 2);
    shrink_rule(dst, 'C', 5);
    shrink_rule(dst, 'D', 2);
}

static int expand(const char *num, char *dst, int maxlen)
{
    *dst = 0;
    int dstlen = 0;
    int len = strlen(num);
    int i;

    for (i = 0; i < len; i++) {
        if (0 == strcmp(num+i, "XC")) {
            strcat(dst, "LXXXX");
            dstlen += 5;
            i++;
        } else if (0 == strcmp(num+i, "XL")) {
            strcat(dst, "XXXX");
            dstlen += 4;
            i++;
        } else if (0 == strcmp(num+i, "IX")) {
            strcat(dst, "VIIII");
            dstlen += 5;
            i++;
        } else if (0 == strcmp(num+i, "IV")) {
            strcat(dst, "IIII");
            dstlen += 4;
            i++;
        } else {
            strncat(dst, num+i, 1);
            dstlen++;
        }
    }
    return dstlen;
}

static void compress(char *dst)
{
    int dstlen = strlen(dst);
    char tmp[dstlen];
    tmp[0] = 0;
    int i;

    for(i = 0; i < dstlen; i++)
    {
        if (0 == strncmp(dst+i, "CCCC", 4)) {
            strcat(tmp, "CD");
            i += 3;
        } else if (0 == strncmp(dst+i, "LXXXX", 5)) {
            strcat(tmp, "XC");
            i += 4;
        } else if (0 == strncmp(dst+i, "XXXX", 4)) {
            strcat(tmp, "XL");
            i += 3;
        } else if (0 == strcmp(dst+i, "VIIII")) {
            strcat(tmp, "IX");
            i += 4;
        } else if (0 == strcmp(dst+i, "IIII")) {
            strcat(tmp, "IV");
            i += 3;
        } else {
            strncat(tmp, dst+i, 1);
        }
    }

    strcpy(dst, tmp);
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
    shrink(dst);
    compress(dst);
}
