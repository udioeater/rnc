#ifndef _FACTS_H_
#define _FACTS_H_

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

#endif /* _FACTS_H_ */
