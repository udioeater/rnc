#include "facts.h"
#include <string.h>
#include <strings.h>
#include <stdbool.h>

const char *lowest_bigger_digit(const char *num, const char digit)
{
    int i = strlen(num) - 1;
    char *idx = index(ORDER, digit);

    while(i >= 0 && index(ORDER, *(num+i)) > idx) { i--; }

    return num + i;
}
