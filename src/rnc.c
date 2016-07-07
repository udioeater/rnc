#include "rnc.h"
#include "elc.h"
#include "facts.h"
#include <string.h>
#include <strings.h>
#include <stdbool.h>

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
    for (int i = 0; i < CONVERSION_COUNT; i++) {
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

    for (int i = 0; i < CONVERSION_COUNT; i++) {
        conversion_t c = SPECIAL_CONVERSIONS[i];
        const char *from = c.little;
        const char *to = c.big;
        replace(dst, dst, from, to);
    }
}

void add(const char *first, const char *second, char *dst, int maxlen)
{
    *dst = 0;

    char ftmp[calculate_expand_len(first)];
    expand(first, ftmp);

    char stmp[calculate_expand_len(second)];
    expand(second, stmp);

    char tmp[strlen(ftmp) + strlen(stmp)];
    combine(tmp, ftmp, stmp);
    compress(tmp, BASIC_CONVERSIONS);
    compress(tmp, SPECIAL_CONVERSIONS);

    int final_len = strlen(tmp);
    if (maxlen < final_len) return;

    strncpy(dst, tmp, final_len);
}

static const conversion_t* find_basic_conversion(const char *little)
{
    for (int i = 0; i < CONVERSION_COUNT; i++) {
        const conversion_t c = BASIC_CONVERSIONS[i];
        if (0 == strncmp(little, c.little, 1))
            return &BASIC_CONVERSIONS[i];
    }

    return NULL;
}

static bool break_up(char *num, const char needed)
{
    const char *break_point = lowest_bigger_digit(num, needed);
    const conversion_t *c = find_basic_conversion(break_point);
    if (NULL == c) return false;

    char tmp[strlen(num)];
    tmp[0] = 0;

    int leading_digits = break_point - num;
    const char *trailing_digits = break_point + 1;

    strncat(tmp, num, leading_digits);
    strcat(tmp, c->big);
    strcat(tmp, trailing_digits);

    strcpy(num, tmp);
    return true;
}

void cancel(char *lhs, char *rhs)
{
    while (strlen(rhs) > 0)
    {
        char digit_to_erase[2] = { rhs[0], 0 };

        if (replace(lhs, lhs, digit_to_erase, "")) {
            replace(rhs, rhs, digit_to_erase, "");
        } else if (!break_up(lhs, digit_to_erase[0])) {
            *lhs = 0;
            return;
        }
    }
}

void subtract(const char* lhs, const char* rhs, char *dst, int maxlen)
{
    *dst = 0;

    char ltmp[calculate_expand_len(lhs)];
    expand(lhs, ltmp);

    char rtmp[calculate_expand_len(lhs)];
    expand(rhs, rtmp);

    char dtmp[calculate_borrow_len(ltmp, rtmp)];
    strcpy(dtmp, ltmp);

    cancel(dtmp, rtmp);
    compress(dtmp, SPECIAL_CONVERSIONS);

    int final_len = strlen(dtmp);
    if (maxlen < final_len) return;

    strcpy(dst, dtmp);
}
