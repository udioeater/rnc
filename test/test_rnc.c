#include <stdlib.h>
#include <check.h>
#include "../src/rnc.h"

START_TEST (add_I_plus_I_returns_II)
{
    int maxlen = 10;
    char answer[maxlen];

    add("I", "I", answer, maxlen);

    ck_assert_str_eq("II", answer);
}
END_TEST

START_TEST (add_II_plus_I_returns_III)
{
    int maxlen = 10;
    char answer[maxlen];

    add("II", "I", answer, maxlen);

    ck_assert_str_eq("III", answer);
}
END_TEST

START_TEST (add_II_plus_II_returns_IV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("II", "II", answer, maxlen);

    ck_assert_str_eq("IV", answer);
}
END_TEST

START_TEST (add_XIII_plus_I_returns_XIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XIII", "I", answer, maxlen);

    ck_assert_str_eq("XIV", answer);
}
END_TEST

START_TEST (add_I_plus_V_returns_VI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("I", "V", answer, maxlen);

    ck_assert_str_eq("VI", answer);
}
END_TEST

START_TEST (add_XI_plus_V_returns_XVI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XI", "V", answer, maxlen);

    ck_assert_str_eq("XVI", answer);
}
END_TEST

START_TEST (add_V_plus_XI_returns_XVI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", "XI", answer, maxlen);

    ck_assert_str_eq("XVI", answer);
}
END_TEST

START_TEST (add_VIII_plus_I_returns_IX)
{
    int maxlen = 10;
    char answer[maxlen];

    add("VIII", "I", answer, maxlen);

    ck_assert_str_eq("IX", answer);
}
END_TEST

START_TEST (add_V_plus_V_returns_X)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", "V", answer, maxlen);

    ck_assert_str_eq("X", answer);
}
END_TEST

START_TEST (add_III_plus_II_returns_V)
{
    int maxlen = 10;
    char answer[maxlen];

    add("III", "II", answer, maxlen);

    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (add_VI_plus_V_returns_XI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("VI", "V", answer, maxlen);

    ck_assert_str_eq("XI", answer);
}
END_TEST

START_TEST (add_XXX_plus_XX_returns_L)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XXX", "XX", answer, maxlen);

    ck_assert_str_eq("L", answer);
}
END_TEST

START_TEST (add_L_plus_LVI_returns_CVI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("L", "LVI", answer, maxlen);

    ck_assert_str_eq("CVI", answer);
}
END_TEST

START_TEST (add_CCCV_plus_CCV_returns_DX)
{
    int maxlen = 10;
    char answer[maxlen];

    add("CCCV", "CCV", answer, maxlen);

    ck_assert_str_eq("DX", answer);
}
END_TEST

START_TEST (add_DX_plus_DI_returns_MXI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("DX", "DI", answer, maxlen);

    ck_assert_str_eq("MXI", answer);
}
END_TEST

START_TEST (add_IV_plus_I_returns_V)
{
    int maxlen = 10;
    char answer[maxlen];

    add("IV", "I", answer, maxlen);

    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (add_V_plus_IX_returns_XIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", "IX", answer, maxlen);

    ck_assert_str_eq("XIV", answer);
}
END_TEST

START_TEST (add_XIV_plus_I_returns_XV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XIV", "I", answer, maxlen);

    ck_assert_str_eq("XV", answer);
}
END_TEST

START_TEST (add_V_plus_CIX_returns_CXIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", "CIX", answer, maxlen);

    ck_assert_str_eq("CXIV", answer);
}
END_TEST

START_TEST (add_XL_plus_X_returns_L)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XL", "X", answer, maxlen);

    ck_assert_str_eq("L", answer);
}
END_TEST

START_TEST (add_XC_plus_X_returns_C)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XC", "X", answer, maxlen);

    ck_assert_str_eq("C", answer);
}
END_TEST

START_TEST (add_XX_plus_XX_returns_XL)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XX", "XX", answer, maxlen);

    ck_assert_str_eq("XL", answer);
}
END_TEST

Suite* rnc_suite(void)
{
    Suite *s;
    TCase *basic;
    TCase *ordering;
    TCase *combining;
    TCase *shorthand;

    s = suite_create("RNC-add");
    basic = tcase_create("basic");
    ordering = tcase_create("ordering");
    combining = tcase_create("combining");
    shorthand = tcase_create("shorthand");

    tcase_add_test(basic, add_I_plus_I_returns_II);
    tcase_add_test(basic, add_II_plus_I_returns_III);
    tcase_add_test(shorthand, add_II_plus_II_returns_IV);
    tcase_add_test(shorthand, add_XIII_plus_I_returns_XIV);
    tcase_add_test(ordering, add_I_plus_V_returns_VI);
    tcase_add_test(ordering, add_XI_plus_V_returns_XVI);
    tcase_add_test(ordering, add_V_plus_XI_returns_XVI);
    tcase_add_test(shorthand, add_VIII_plus_I_returns_IX);
    tcase_add_test(combining, add_V_plus_V_returns_X);
    tcase_add_test(combining, add_III_plus_II_returns_V);
    tcase_add_test(combining, add_VI_plus_V_returns_XI);
    tcase_add_test(combining, add_XXX_plus_XX_returns_L);
    tcase_add_test(combining, add_L_plus_LVI_returns_CVI);
    tcase_add_test(combining, add_CCCV_plus_CCV_returns_DX);
    tcase_add_test(combining, add_DX_plus_DI_returns_MXI);
    tcase_add_test(shorthand, add_IV_plus_I_returns_V);
    tcase_add_test(shorthand, add_V_plus_IX_returns_XIV);
    tcase_add_test(shorthand, add_XIV_plus_I_returns_XV);
    tcase_add_test(shorthand, add_V_plus_CIX_returns_CXIV);
    tcase_add_test(shorthand, add_XL_plus_X_returns_L);
    tcase_add_test(shorthand, add_XC_plus_X_returns_C);
    tcase_add_test(shorthand, add_XX_plus_XX_returns_XL);

    suite_add_tcase(s, basic);
    suite_add_tcase(s, ordering);
    suite_add_tcase(s, combining);
    suite_add_tcase(s, shorthand);

    return s;
}

int main(void)
{
    int failures;
    Suite *s;
    SRunner *sr;
    
    s = rnc_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
