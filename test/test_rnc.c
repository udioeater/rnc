#include <stdlib.h>
#include <check.h>
#include "../src/rnc.h"

START_TEST (add_I_plus_I_returns_II)
{
    int maxlen = 10;
    char answer[maxlen];

    add("I", 1, "I", 1, answer, maxlen);

    ck_assert_str_eq("II", answer);
}
END_TEST

START_TEST (add_II_plus_I_returns_III)
{
    int maxlen = 10;
    char answer[maxlen];

    add("II", 2, "I", 1, answer, maxlen);

    ck_assert_str_eq("III", answer);
}
END_TEST

START_TEST (add_II_plus_II_returns_IV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("II", 2, "II", 2, answer, maxlen);

    ck_assert_str_eq("IV", answer);
}
END_TEST

START_TEST (add_XIII_plus_I_returns_XIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XIII", 4, "I", 1, answer, maxlen);

    ck_assert_str_eq("XIV", answer);
}
END_TEST

START_TEST (add_I_plus_V_returns_VI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("I", 1, "V", 1, answer, maxlen);

    ck_assert_str_eq("VI", answer);
}
END_TEST

START_TEST (add_XI_plus_V_returns_XVI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XI", 2, "V", 1, answer, maxlen);

    ck_assert_str_eq("XVI", answer);
}
END_TEST

START_TEST (add_V_plus_XI_returns_XVI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", 1, "XI", 2, answer, maxlen);

    ck_assert_str_eq("XVI", answer);
}
END_TEST

START_TEST (add_VIII_plus_I_returns_IX)
{
    int maxlen = 10;
    char answer[maxlen];

    add("VIII", 4, "I", 1, answer, maxlen);

    ck_assert_str_eq("IX", answer);
}
END_TEST

START_TEST (add_V_plus_V_returns_X)
{
    int maxlen = 10;
    char answer[maxlen];

    add("V", 1, "V", 1, answer, maxlen);

    ck_assert_str_eq("X", answer);
}
END_TEST

Suite* rnc_suite(voi)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RNC");
    tc_core = tcase_create("add");

    tcase_add_test(tc_core, add_I_plus_I_returns_II);
    tcase_add_test(tc_core, add_II_plus_I_returns_III);
    tcase_add_test(tc_core, add_II_plus_II_returns_IV);
    tcase_add_test(tc_core, add_XIII_plus_I_returns_XIV);
    tcase_add_test(tc_core, add_I_plus_V_returns_VI);
    tcase_add_test(tc_core, add_XI_plus_V_returns_XVI);
    tcase_add_test(tc_core, add_V_plus_XI_returns_XVI);
    tcase_add_test(tc_core, add_VIII_plus_I_returns_IX);
    tcase_add_test(tc_core, add_V_plus_V_returns_X);
    suite_add_tcase(s, tc_core);

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
