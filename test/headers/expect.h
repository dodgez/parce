#ifndef expect_h
#define expect_h

#include <stdio.h>
#include <string.h>

#define TEST_PASSED 0
#define TEST_FAILED 1

void run_suite(char* name);
void end_suite();

void run_test(char* name);
void end_test();

int expect_equal_int(int a, int b);
int expect_equal_str(char* a, char* b);

char* TEST_NAME;
int HAS_TEST_PASSED;

#endif
