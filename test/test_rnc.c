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

START_TEST (add_CC_plus_CC_returns_CD)
{
    int maxlen = 10;
    char answer[maxlen];

    add("CC", "CC", answer, maxlen);

    ck_assert_str_eq("CD", answer);
}
END_TEST

START_TEST (add_LX_plus_XXX_returns_XC)
{
    int maxlen = 10;
    char answer[maxlen];

    add("LX", "XXX", answer, maxlen);

    ck_assert_str_eq("XC", answer);
}
END_TEST

START_TEST (add_LXIII_plus_XXXI_returns_XCIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("LXIII", "XXXI", answer, maxlen);

    ck_assert_str_eq("XCIV", answer);
}
END_TEST

START_TEST (add_CCII_plus_CCII_returns_CDIV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("CCII", "CCII", answer, maxlen);

    ck_assert_str_eq("CDIV", answer);
}
END_TEST

START_TEST (add_XX_plus_XXV_returns_XLV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("XX", "XXV", answer, maxlen);

    ck_assert_str_eq("XLV", answer);
}
END_TEST

START_TEST (add_DCCV_plus_CCX_returns_CMXV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("DCCV", "CCX", answer, maxlen);

    ck_assert_str_eq("CMXV", answer);
}
END_TEST

START_TEST (add_returns_empty_string_when_maxlen_is_too_small)
{
    int maxlen = 2;
    char answer[maxlen];

    add("II", "I", answer, maxlen);
    ck_assert_str_eq("", answer);
}
END_TEST

START_TEST (add_handles_too_large_intermediate_value)
{
    int maxlen = 5;
    char answer[maxlen + 6];
    strcpy (answer+maxlen, "hello");

    add("XC", "CM", answer, maxlen);
    ck_assert_str_eq("CMXC", answer);
    ck_assert_str_eq("hello", answer+maxlen);
}
END_TEST

START_TEST (add_returns_when_result_is_small_enough)
{
    int maxlen = 1;
    char answer[maxlen];

    add("IV", "I", answer, maxlen);
    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (add_CDI_plus_C_returns_DI)
{
    int maxlen = 10;
    char answer[maxlen];

    add("CDI", "C", answer, maxlen);
    ck_assert_str_eq("DI", answer);
}
END_TEST

START_TEST (add_CMV_plus_C_returns_MV)
{
    int maxlen = 10;
    char answer[maxlen];

    add("CMV", "C", answer, maxlen);
    ck_assert_str_eq("MV", answer);
}
END_TEST

Suite* addition_suite(void)
{
    Suite *s;
    TCase *basic;
    TCase *ordering;
    TCase *combining;
    TCase *shorthand;
    TCase *errors;

    s = suite_create("RNC-addition");
    basic = tcase_create("basic");
    ordering = tcase_create("ordering");
    combining = tcase_create("combining");
    shorthand = tcase_create("shorthand");
    errors = tcase_create("errors");

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
    tcase_add_test(shorthand, add_CC_plus_CC_returns_CD);
    tcase_add_test(shorthand, add_LX_plus_XXX_returns_XC);
    tcase_add_test(shorthand, add_LXIII_plus_XXXI_returns_XCIV);
    tcase_add_test(shorthand, add_CCII_plus_CCII_returns_CDIV);
    tcase_add_test(shorthand, add_XX_plus_XXV_returns_XLV);
    tcase_add_test(shorthand, add_DCCV_plus_CCX_returns_CMXV);
    tcase_add_test(errors, add_returns_empty_string_when_maxlen_is_too_small);
    tcase_add_test(errors, add_handles_too_large_intermediate_value);
    tcase_add_test(errors, add_returns_when_result_is_small_enough);
    tcase_add_test(shorthand, add_CDI_plus_C_returns_DI);
    tcase_add_test(shorthand, add_CMV_plus_C_returns_MV);

    suite_add_tcase(s, basic);
    suite_add_tcase(s, ordering);
    suite_add_tcase(s, combining);
    suite_add_tcase(s, shorthand);
    suite_add_tcase(s, errors);

    return s;
}

START_TEST (subtract_II_minus_I_returns_I)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("II", "I", answer, maxlen);

    ck_assert_str_eq("I", answer);
}
END_TEST

START_TEST (subtract_VI_minus_I_returns_V)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("VI", "I", answer, maxlen);

    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (subtract_XVI_minus_V_returns_XI)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("XVI", "V", answer, maxlen);

    ck_assert_str_eq("XI", answer);
}
END_TEST

START_TEST (subtract_XVI_minus_XI_returns_V)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("XVI", "XI", answer, maxlen);

    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (subtract_MDCLXVI_minus_DLXI_returns_MCV)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("MDCLXVI", "DLXI", answer, maxlen);

    ck_assert_str_eq("MCV", answer);
}
END_TEST

START_TEST (subtract_IV_minus_I_returns_III)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("IV", "I", answer, maxlen);

    ck_assert_str_eq("III", answer);
}
END_TEST

START_TEST (subtract_IX_minus_VII_returns_II)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("IX", "VII", answer, maxlen);

    ck_assert_str_eq("II", answer);
}
END_TEST

START_TEST (subtract_V_minus_II_returns_III)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("V", "II", answer, maxlen);

    ck_assert_str_eq("III", answer);
}
END_TEST

START_TEST (subtract_X_minus_V_returns_V)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("X", "V", answer, maxlen);

    ck_assert_str_eq("V", answer);
}
END_TEST

START_TEST (subtract_X_minus_IV_returns_VI)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("X", "IV", answer, maxlen);

    ck_assert_str_eq("VI", answer);
}
END_TEST

START_TEST (subtract_XX_minus_V_returns_XV)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("XX", "V", answer, maxlen);

    ck_assert_str_eq("XV", answer);
}
END_TEST

START_TEST (subtract_L_minus_XX_returns_XXX)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("L", "XX", answer, maxlen);

    ck_assert_str_eq("XXX", answer);
}
END_TEST

START_TEST (subtract_CC_minus_L_returns_CL)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("CC", "L", answer, maxlen);

    ck_assert_str_eq("CL", answer);
}
END_TEST

START_TEST (subtract_DD_minus_CC_returns_DCCC)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("DD", "CC", answer, maxlen);

    ck_assert_str_eq("DCCC", answer);
}
END_TEST

START_TEST (subtract_MM_minus_D_returns_MD)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("MM", "D", answer, maxlen);

    ck_assert_str_eq("MD", answer);
}
END_TEST

START_TEST (subtract_XX_minus_II_returns_XVIII)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("XX", "II", answer, maxlen);

    ck_assert_str_eq("XVIII", answer);
}
END_TEST

START_TEST (subtract_MX_minus_D_returns_DX)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("MX", "D", answer, maxlen);

    ck_assert_str_eq("DX", answer);
}
END_TEST

START_TEST (subtract_XLII_minus_XVII_returns_XXV)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("XLII", "XVII", answer, maxlen);

    ck_assert_str_eq("XXV", answer);
}
END_TEST

START_TEST (subtract_returns_empty_string_when_lhs_is_smaller)
{
    int maxlen = 10;
    char answer[maxlen];

    subtract("I", "V", answer, maxlen);

    ck_assert_str_eq("", answer);
}
END_TEST

Suite* subtraction_suite(void)
{
    Suite *s;
    TCase *basic;
    TCase *expand;
    TCase *borrow;
    TCase *invalid;

    s = suite_create("RNC-subtraction");
    basic = tcase_create("basic");
    expand = tcase_create("expand");
    borrow = tcase_create("borrow");
    invalid = tcase_create("invalid");

    tcase_add_test(basic, subtract_II_minus_I_returns_I);
    tcase_add_test(basic, subtract_VI_minus_I_returns_V);
    tcase_add_test(basic, subtract_XVI_minus_V_returns_XI);
    tcase_add_test(basic, subtract_XVI_minus_XI_returns_V);
    tcase_add_test(basic, subtract_MDCLXVI_minus_DLXI_returns_MCV);
    tcase_add_test(expand, subtract_IV_minus_I_returns_III);
    tcase_add_test(expand, subtract_IX_minus_VII_returns_II);
    tcase_add_test(borrow, subtract_V_minus_II_returns_III);
    tcase_add_test(borrow, subtract_X_minus_V_returns_V);
    tcase_add_test(borrow, subtract_X_minus_IV_returns_VI);
    tcase_add_test(borrow, subtract_XX_minus_V_returns_XV);
    tcase_add_test(borrow, subtract_L_minus_XX_returns_XXX);
    tcase_add_test(borrow, subtract_CC_minus_L_returns_CL);
    tcase_add_test(borrow, subtract_DD_minus_CC_returns_DCCC);
    tcase_add_test(borrow, subtract_MM_minus_D_returns_MD);
    tcase_add_test(borrow, subtract_XX_minus_II_returns_XVIII);
    tcase_add_test(borrow, subtract_MX_minus_D_returns_DX);
    tcase_add_test(borrow, subtract_XLII_minus_XVII_returns_XXV);
    tcase_add_test(invalid, subtract_returns_empty_string_when_lhs_is_smaller);

    suite_add_tcase(s, basic);
    suite_add_tcase(s, expand);
    suite_add_tcase(s, borrow);
    suite_add_tcase(s, invalid);

    return s;
}

int main(void)
{
    int failures;
    Suite *s;
    SRunner *sr;
    
    s = addition_suite();
    sr = srunner_create(s);

    s = subtraction_suite();
    srunner_add_suite(sr, s);

    srunner_run_all(sr, CK_NORMAL);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
