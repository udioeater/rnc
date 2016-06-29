#include "rnc.h"
#include <string.h>
#include <stdbool.h>

static const char ORDER[7] = "MDCLXVI";
static const int MAX_EXPAND_MULTIPLIER = 3;
static const int BORROW_MULTIPLIER = 5;

typedef struct {
    char *little;
    char *big;
} conversion_t;

static const int CONVERSION_COUNT = 6;
static const conversion_t BASIC_CONVERSIONS[] = {
    { .little = "V", .big = "IIIII" },
    { .little = "X", .big = "VV" },
    { .little = "L", .big = "XXXXX" },
    { .little = "C", .big = "LL" },
    { .little = "D", .big = "CCCCC" },
    { .little = "M", .big = "DD" },
};

static const conversion_t SPECIAL_CONVERSIONS[] = {
    { .little = "CM", .big = "DCCCC" },
    { .little = "CD", .big = "CCCC" },
    { .little = "XC", .big = "LXXXX" },
    { .little = "XL", .big = "XXXX" },
    { .little = "IX", .big = "VIIII" },
    { .little = "IV", .big = "IIII" },
};

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

static bool replace(char *dst, const char *src, const char *search, const char *replacement)
{
    const char *match = strstr(src, search);
    if (NULL != match) {
        int newlen = strlen(src) - strlen(search) + strlen(replacement);
        char tmp[newlen];
        tmp[0] = 0;

        int leading_digits = match - src;
        const char *trailing_digits = match + strlen(search);

        strncat(tmp, src, leading_digits);
        strcat(tmp, replacement);
        strcat(tmp, trailing_digits);

        strcpy(dst, tmp);
        return true;
    }

    return false;
}

static void compress(char *dst, const conversion_t *conversion_set)
{
    int i;
    for (i = 0; i < CONVERSION_COUNT; i++) {
        const conversion_t *c = conversion_set + i;
        const char *from = c->big;
        const char *to = c->little;
        replace(dst, dst, from, to);
    }
}

static void expand(const char *num, char *dst)
{
    *dst = 0;
    strcpy(dst, num);
    int i;

    for (i = 0; i < CONVERSION_COUNT; i++) {
        conversion_t c = SPECIAL_CONVERSIONS[i];
        const char *from = c.little;
        const char *to = c.big;
        replace(dst, dst, from, to);
    }
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
    compress(tmp, BASIC_CONVERSIONS);
    compress(tmp, SPECIAL_CONVERSIONS);

    int final_len = strlen(tmp);
    if (maxlen < final_len) return;

    strncpy(dst, tmp, final_len);
}

static const char *find_digit_to_break_up(const char *num, const char needed)
{
    int i = strlen(num) - 1;
    char *idx = index(ORDER, needed);

    while(i >= 0 && index(ORDER, *(num+i)) > idx) {
        i--;
    }

    return num + i;
}

static const conversion_t* find_basic_conversion(const char *little)
{
    int i;
    for (i = 0; i < CONVERSION_COUNT; i++) {
        const conversion_t c = BASIC_CONVERSIONS[i];
        if (0 == strncmp(little, c.little, 1))
            return &BASIC_CONVERSIONS[i];
    }

    return NULL;
}

static void break_up(char *num, const char needed)
{
    const char *break_point = find_digit_to_break_up(num, needed);
    const conversion_t *c = find_basic_conversion(break_point);

    int leading_digits = break_point - num;
    char tmp[strlen(num)];
    tmp[0] = 0;

    strncat(tmp, num, leading_digits);
    strcat(tmp, c->big);
    strcat(tmp, break_point + 1);

    strcpy(num, tmp);
}

void subtract(const char* lhs, const char* rhs, char *dst, int maxlen)
{
    *dst = 0;
    int l_len = strlen(lhs);
    int r_len = strlen(rhs);

    char ltmp[l_len * MAX_EXPAND_MULTIPLIER * BORROW_MULTIPLIER];
    expand(lhs, ltmp);

    char rtmp[r_len * MAX_EXPAND_MULTIPLIER];
    expand(rhs, rtmp);

    while (strlen(rtmp) > 0)
    {
        char digit_to_erase[2] = { rtmp[0], 0 };

        if (replace(dst, ltmp, digit_to_erase, "")) {
            replace(rtmp, rtmp, digit_to_erase, "");
            strcpy(ltmp, dst);
        } else {
            break_up(ltmp, digit_to_erase[0]);
        }
    }
}
