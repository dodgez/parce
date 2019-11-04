#include "expect.h"

void run_suite(char* name) {
  printf("\n%s:\n", name);
}

void run_test(char* name) {
  TEST_NAME = name;
  HAS_TEST_PASSED = TEST_PASSED;
}

void end_test() {
  if (HAS_TEST_PASSED == TEST_PASSED) {
    printf("\t-/ %s\n", TEST_NAME);
  }
}

void end_suite() {
  printf("\n");
}

int expect_equal_int(int a, int b) {
  if (a == b) {
    return TEST_PASSED;
  } else {
    HAS_TEST_PASSED = TEST_FAILED;
    printf("\txx %s expected %d to equal %d\n", TEST_NAME, a, b);
    return TEST_FAILED;
  }
}

int expect_equal_str(char* a, char* b) {
  if (strcmp(a, b) == 0) {
    return TEST_PASSED;
  } else {
    HAS_TEST_PASSED = TEST_FAILED;
    printf("\txx %s expected %s to equal %s\n", TEST_NAME, a, b);
    return TEST_FAILED;
  }
}
