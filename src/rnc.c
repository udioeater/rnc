#include "rnc.h"
#include <string.h>
#include <stdbool.h>

static const char ORDER[7] = "MDCLXVI";
static const int MAX_EXPAND_MULTIPLIER = 3;
static const int MAX_BORROW_MULTIPLIER = 5;

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

static void replace_to_end(char *dst, char *search)
{
    char *idx = strstr(dst, search);
    if (NULL != idx) {
        char *replace_with = index(ORDER, search[0]) - 1;
        char tmp[strlen(dst)];
        tmp[0] = 0;

        strncat(tmp, replace_with, 1);

        const char *trailing_digits = idx + strlen(search);
        strcat(tmp, trailing_digits);

        strcpy(dst+(idx-dst), tmp);
    }
}

static void shrink(char *dst)
{
    replace_to_end(dst, "IIIII");
    replace_to_end(dst, "VV");
    replace_to_end(dst, "XXXXX");
    replace_to_end(dst, "LL");
    replace_to_end(dst, "CCCCC");
    replace_to_end(dst, "DD");
}

static int replace_from_front(char *dst, const char *src, const char *search, const char *replacement)
{
    char *idx = strstr(src, search);
    if (NULL != idx) {
        int digits_before_match = idx - src;
        strncat(dst, src, digits_before_match);
        strcat(dst, replacement);
        return strlen(search) + digits_before_match;
    }
    return 0;
}

static void expand(const char *num, char *dst)
{
    *dst = 0;
    int i = 0;

    i += replace_from_front(dst, num+i, "XC", "LXXXX");
    i += replace_from_front(dst, num+i, "XL", "XXXX");
    i += replace_from_front(dst, num+i, "IX", "VIIII");
    i += replace_from_front(dst, num+i, "IV", "IIII");

    strcat(dst, num+i);
}

static void compress(char *dst)
{
    int dstlen = strlen(dst);
    char tmp[dstlen];
    tmp[0] = 0;
    int i = 0;

    i += replace_from_front(tmp, dst+i, "DCCCC", "CM");
    i += replace_from_front(tmp, dst+i, "CCCC", "CD");
    i += replace_from_front(tmp, dst+i, "LXXXX", "XC");
    i += replace_from_front(tmp, dst+i, "XXXX", "XL");
    i += replace_from_front(tmp, dst+i, "VIIII", "IX");
    i += replace_from_front(tmp, dst+i, "IIII", "IV");
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
    shrink(tmp);
    compress(tmp);

    int final_len = strlen(tmp);
    if (maxlen < final_len) return;

    strncpy(dst, tmp, final_len);
}

static bool remove(char *dst, const char *src, const char *search)
{
    strcpy(dst, src);
    char *idx = strstr(src, search);
    if (NULL != idx) {
        int digits_before_match = idx - src;
        const char *trailing_digits = idx + strlen(search);
        strcpy(dst + digits_before_match, trailing_digits);
        return true;
    }

    return false;
}

static void break_up(char *num)
{
    int numlen = strlen(num);
    char *last_digit = num + numlen - 1;

    if (0 == strcmp(last_digit, "C")) {
        strcpy(last_digit, "LL");
    } else if (0 == strcmp(last_digit, "L")) {
        strcpy(last_digit, "XXXXX");
    } else if (0 == strcmp(last_digit, "X")) {
        strcpy(last_digit, "VV");
    } else {
        strcpy(last_digit, "IIIII");
    }
}

void subtract(const char* lhs, const char* rhs, char *dst, int maxlen)
{
    *dst = 0;

    int max_multiplier = MAX_EXPAND_MULTIPLIER * MAX_BORROW_MULTIPLIER;
    char ltmp[strlen(lhs) * max_multiplier];
    expand(lhs, ltmp);

    char rtmp[strlen(rhs)];
    expand(rhs, rtmp);

    while (strlen(rtmp) > 0)
    {
        char digit_to_erase[2] = { rtmp[0], 0 };
        if (remove(dst, ltmp, digit_to_erase)) {
            remove(rtmp, rtmp, digit_to_erase);
            strcpy(ltmp, dst);
        } else {
            break_up(ltmp);
        }
    }
}
