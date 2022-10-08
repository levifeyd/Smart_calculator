#include <string.h>
#include <stdio.h>
#include <check.h>
#include "calculator.h"
#define EPS 1e-7

START_TEST(Test1) {
    char expression[] = {"(2+3)*5"};
    char* pexp = &expression[0];
    double result = 0;
    startuem(pexp, &result);
    ck_assert_float_eq(result, 25.0);
}
END_TEST

START_TEST(Test2) {
    char expression[] = {"1/2 + (2+3)/(sin(9-2)^2-6/7)"};
    char* pexp = &expression[0];
    double result = 0;
    double result2 = -11.2506;
    startuem(pexp, &result);
    ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

START_TEST(Test3) {
    char expression[] = {"1/2+(2+3"};
    char* pexp = &expression[0];
    double result = 0;
    ck_assert_int_eq(startuem(pexp, &result), 18);
}
END_TEST

START_TEST(Test4) {
    char expression[] = {"1/2+(2.3.5+3)"};
    char* pexp = &expression[0];
    double result = 0;
    ck_assert_int_eq(startuem(pexp, &result), 1);
}
END_TEST

START_TEST(Test5) {
    char expression[] = {"**"};
    char* pexp = &expression[0];
    double result = 0;
    ck_assert_int_eq(startuem(pexp, &result), 18);
}
END_TEST

START_TEST(Test6) {
    char expression[] = {"sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4%2)*log(5)"};
    char* pexp = &expression[0];
    double result = 0;
    double result2 = -1.47532;
    startuem(pexp, &result);
    ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

START_TEST(Test7) {
    char expression[] = {"ln(2)+log(5)"};
    char* pexp = &expression[0];
    double result = 0;
    double result2 =  1.392117;
    startuem(pexp, &result);
    ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

START_TEST(Test8) {
    char expression[] = {"asin(1)+acos(0)"};
    char* pexp = &expression[0];
    double result = 0;
    double result2 =  3.14159;
    startuem(pexp, &result);
    ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

Suite *calculator_tests_create() {
    Suite *calculator = suite_create("calculator");
    TCase *calculator_tests = tcase_create("calculator");
    tcase_add_test(calculator_tests, Test1);
    tcase_add_test(calculator_tests, Test2);
    tcase_add_test(calculator_tests, Test3);
    tcase_add_test(calculator_tests, Test4);
    tcase_add_test(calculator_tests, Test5);
    tcase_add_test(calculator_tests, Test6);
    tcase_add_test(calculator_tests, Test7);
    tcase_add_test(calculator_tests, Test8);
    suite_add_tcase(calculator, calculator_tests);
    return calculator;
}

int main() {
    Suite *calculator = calculator_tests_create();
    SRunner *calculator_runner = srunner_create(calculator);
    int number_failed;
    srunner_run_all(calculator_runner, FP_NORMAL);
    number_failed = srunner_ntests_failed(calculator_runner);
    srunner_free(calculator_runner);

    return number_failed == 0 ? 0 : 1;
}
