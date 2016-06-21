#include <stdlib.h>
#include <check.h>

START_TEST (test)
{
    ck_assert_int_eq(1, 2);
}
END_TEST

Suite* rnc_suite(voi)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RNC");
    tc_core = tcase_create("test");

    tcase_add_test(tc_core, test);
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
