#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "tripler.h"

// https://libcheck.github.io/check/doc/check_html/check_3.html
// To run unit tests with Check, we must create some test cases, aggregate them into a suite, and run them with a suite runner.
// https://www.ccs.neu.edu/home/skotthe/classes/cs5600/fall/2015/labs/intro-check.html


int doubler(int x) {
    return x * 2;
}


START_TEST(test_doubler) {
    ck_assert_int_eq(doubler(1), 2);
    ck_assert_int_eq(doubler(2), 4);
    ck_assert_int_eq(doubler(3), 6);
}
END_TEST


START_TEST(test_tripler) {
    ck_assert_int_eq(tripler(1), 3);
    ck_assert_int_eq(tripler(2), 6);
    ck_assert_int_eq(tripler(3), 9);
}
END_TEST


Suite *my_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("MySuite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_doubler);
    tcase_add_test(tc_core, test_tripler);
    suite_add_tcase(s, tc_core);

    return s;
}


int main() {
    printf("taking a look at the check framework again\n");
    printf("doubler(2) is %d\n", doubler(2));
    printf("doubler(4) is %d\n", doubler(4));
    printf("tripler(1) is %d\n", tripler(1));

    printf("running tests with check..\n");

    int no_failed = 0;

    Suite *s;
    SRunner *runner;

    s = my_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
