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

Suite* rnc_suite(voi)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RNC");
    tc_core = tcase_create("add");

    tcase_add_test(tc_core, add_I_plus_I_returns_II);
    tcase_add_test(tc_core, add_II_plus_I_returns_III);
    tcase_add_test(tc_core, add_II_plus_II_returns_IV);
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
