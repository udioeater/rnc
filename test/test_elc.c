#include <stdlib.h>
#include <check.h>
#include "../src/elc.h"

START_TEST (calculate_expand_len_II)
{
    char expected_expansion[] = "II";
    int needed_size = sizeof(expected_expansion);
    ck_assert_int_eq(needed_size, calculate_expand_len("II"));
}
END_TEST

START_TEST (calculate_expand_len_IV)
{
    char expected_expansion[] = "IIII";
    int needed_size = sizeof(expected_expansion);
    ck_assert_int_eq(needed_size, calculate_expand_len("IV"));
}
END_TEST

START_TEST (calculate_expand_len_IX)
{
    char expected_expansion[] = "VIIII";
    int needed_size = sizeof(expected_expansion);
    ck_assert_int_eq(needed_size, calculate_expand_len("IX"));
}
END_TEST

START_TEST (calculate_expand_len_XLIV)
{
    char expected_expansion[] = "XXXXIIII";
    int needed_size = sizeof(expected_expansion);
    ck_assert_int_eq(needed_size, calculate_expand_len("XLIV"));
}
END_TEST

Suite* suite(void)
{
    Suite *s;
    TCase *basic;

    s = suite_create("ELC-expand");
    basic = tcase_create("basic");

    tcase_add_test(basic, calculate_expand_len_II);
    tcase_add_test(basic, calculate_expand_len_IV);
    tcase_add_test(basic, calculate_expand_len_IX);
    tcase_add_test(basic, calculate_expand_len_XLIV);

    suite_add_tcase(s, basic);

    return s;
}

int main(void)
{
    int failures;
    Suite *s;
    SRunner *sr;
    
    s = suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
