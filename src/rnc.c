#include "rnc.h"
#include <string.h>
#include <stdbool.h>

static const char ORDER[7] = "MDCLXVI";
static const int MAX_EXPAND_MULTIPLIER = 3;

static void combine(char *dst, const char *first, const char *second)
{
    *dst = 0;
    int total_len = strlen(first) + strlen(second);
    int i = 0;
    int j = 0;

    while (strlen(dst) < total_len) {
        char *f_digit = index(ORDER, *(first+i));
        char *s_digit = index(ORDER, *(second+j));
        bool used_all_s_digits = (NULL == s_digit);
        bool f_digit_comes_before_s = (f_digit < s_digit);
        bool take_next_digit_from_f = (used_all_s_digits || f_digit_comes_before_s);

        if (take_next_digit_from_f) {
            strncat(dst, first+i, 1);
            i++;
        } else {
            strncat(dst, second+j, 1);
            j++;
        }
    }
}

static void shrink(char *dst, char *search)
{
    int dstlen = strlen(dst);
    char search_len = strlen(search);
    char tmp[dstlen];
    tmp[0] = 0;

    char *idx = index(dst, search[0]);
    if (NULL != idx && 0 == strncmp(idx, search, search_len)) {
        char *replace_with = index(ORDER, search[0]) - 1;
        strncat(tmp, replace_with, 1);
        strcat(tmp, idx+search_len);
        strcpy(dst+(idx-dst), tmp);
    }
}

static void shrink_basic(char *dst)
{
    shrink(dst, "IIIII");
    shrink(dst, "VV");
    shrink(dst, "XXXXX");
    shrink(dst, "LL");
    shrink(dst, "CCCCC");
    shrink(dst, "DD");
}

static int replace(char *dst, const char *src, const char *search, const char *replacement)
{
    char *idx = strstr(src, search);
    if (NULL != idx) {
        int chars_before_match = idx - src;
        strncat(dst, src, chars_before_match);
        strcat(dst, replacement);
        return strlen(search) + chars_before_match;
    }
    return 0;
}

static void expand(const char *num, char *dst)
{
    *dst = 0;
    int i = 0;

    i += replace(dst, num+i, "XC", "LXXXX");
    i += replace(dst, num+i, "XL", "XXXX");
    i += replace(dst, num+i, "IX", "VIIII");
    i += replace(dst, num+i, "IV", "IIII");

    strcat(dst, num+i);
}

static void compress(char *dst)
{
    int dstlen = strlen(dst);
    char tmp[dstlen];
    tmp[0] = 0;
    int i = 0;

    i += replace(tmp, dst+i, "DCCCC", "CM");
    i += replace(tmp, dst+i, "CCCC", "CD");
    i += replace(tmp, dst+i, "LXXXX", "XC");
    i += replace(tmp, dst+i, "XXXX", "XL");
    i += replace(tmp, dst+i, "VIIII", "IX");
    i += replace(tmp, dst+i, "IIII", "IV");
    strcat(tmp, dst+i);

    strcpy(dst, tmp);
}

void add(const char *first, const char *second, char *dst, int maxlen)
{
    *dst = 0;
    int flen = strlen(first);
    int slen = strlen(second);

    char ftmp[flen * MAX_EXPAND_MULTIPLIER];
    expand(first, ftmp);

    char stmp[slen * MAX_EXPAND_MULTIPLIER];
    expand(second, stmp);

    char tmp[strlen(ftmp) + strlen(stmp)];
    combine(tmp, ftmp, stmp);
    shrink_basic(tmp);
    compress(tmp);

    int final_len = strlen(tmp);
    if (maxlen < final_len) return;

    strncpy(dst, tmp, final_len);
}
