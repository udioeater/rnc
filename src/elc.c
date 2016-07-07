#include "elc.h"
#include "facts.h"
#include <string.h>
#include <strings.h>
#include <stdbool.h>

int calculate_expand_len(const char *num)
{
    int len = strlen(num);
    for (int i = 0; i < CONVERSION_COUNT; i++)
    {
        if (NULL != strstr(num, SPECIAL_CONVERSIONS[i].little)) {
            len -= 2;
            len += strlen(SPECIAL_CONVERSIONS[i].big);
        }
    }

    return len+1;
}

const char *lowest_bigger_digit(const char *num, const char digit)
{
    int i = strlen(num) - 1;
    char *idx = index(ORDER, digit);

    while(i >= 0 && index(ORDER, *(num+i)) > idx) { i--; }

    return num + i;
}

int calculate_borrow_len(const char *lhs, const char *rhs)
{
    int len = strlen(lhs);
    int j = 0;

    for (int i = 0; i < strlen(rhs); i++)
    {
        char digit_to_find[2] = { rhs[i], 0 };
        if (NULL != strstr(lhs+j, digit_to_find)) {
            j++;
            continue;
        }
        while (rhs[i] == digit_to_find[0]) i++;
        char expand_digit[2] = { 0, 0 };
        expand_digit[0] = *lowest_bigger_digit(lhs+j, digit_to_find[0]);

        conversion_t c = { .little = "", .big = "" };
        int k;
        for (k = 0; k < CONVERSION_COUNT; k++) {
            if (digit_to_find[0] == BASIC_CONVERSIONS[k].big[0]) {
                c = BASIC_CONVERSIONS[k];
                break;
            }
        }

        if (c.little[0] == expand_digit[0]) {
            len += strlen(c.big) - 1;
        }

        while (c.little[0] != expand_digit[0] && k < CONVERSION_COUNT)
        {
            c = BASIC_CONVERSIONS[k++];
            len += strlen(c.big) - 1;
        }

        if (c.little[0] != expand_digit[0]) return 0;
    }

    return len+1;
}
