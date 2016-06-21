#include "rnc.h"
#include <string.h>

void add(const char *first, int flen, const char *second, int slen, char *dst, int maxlen)
{
    strncpy(dst, first, flen);
    strncpy(dst+flen, second, slen);
}
