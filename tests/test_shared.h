#ifndef _TEST_SHARED_H
#define _TEST_SHARED_H

#define INVALID_VALUE    9999

#define TEST_ARRLEN      13
static const int arr1[TEST_ARRLEN] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0};
static const int arr2[TEST_ARRLEN] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};

static const int arr1_expected[TEST_ARRLEN] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static const int arr2_expected[TEST_ARRLEN] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0};

#endif
