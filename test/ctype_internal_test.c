/*
 * Copyright 2017 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include "testutil.h"
#include "internal/ctype.h"
#include "../e_os.h"
#include <ctype.h>
#include <stdio.h>

static int test_ctype_chars(int n)
{
    return TEST_int_eq(isalnum(n) != 0, ossl_isalnum(n) != 0)
           && TEST_int_eq(isalpha(n) != 0, ossl_isalpha(n) != 0)
           && TEST_int_eq(isascii(n) != 0, ossl_isascii(n) != 0)
           && TEST_int_eq(isblank(n) != 0, ossl_isblank(n) != 0)
           && TEST_int_eq(iscntrl(n) != 0, ossl_iscntrl(n) != 0)
           && TEST_int_eq(isdigit(n) != 0, ossl_isdigit(n) != 0)
           && TEST_int_eq(isgraph(n) != 0, ossl_isgraph(n) != 0)
           && TEST_int_eq(islower(n) != 0, ossl_islower(n) != 0)
           && TEST_int_eq(isprint(n) != 0, ossl_isprint(n) != 0)
           && TEST_int_eq(ispunct(n) != 0, ossl_ispunct(n) != 0)
           && TEST_int_eq(isspace(n) != 0, ossl_isspace(n) != 0)
           && TEST_int_eq(isupper(n) != 0, ossl_isupper(n) != 0)
           && TEST_int_eq(isxdigit(n) != 0, ossl_isxdigit(n) != 0);
}

static int test_ctype_negative(int n)
{
    return test_ctype_chars(-n);
}

static struct {
    int u;
    int l;
} case_change[] = {
    { 'A', 'a' },
    { 'X', 'x' },
    { 'Z', 'z' },
    { '0', '0' },
    { '%', '%' },
    { '~', '~' },
    {   0,   0 },
    { EOF, EOF },
    { 333, 333 },
    { -333, -333 },
    { -128, -128 }
};

static int test_ctype_toupper(int n)
{
    return TEST_int_eq(ossl_toupper(case_change[n].l), case_change[n].u)
           && TEST_int_eq(ossl_toupper(case_change[n].u), case_change[n].u);
}

static int test_ctype_tolower(int n)
{
    return TEST_int_eq(ossl_tolower(case_change[n].u), case_change[n].l)
           && TEST_int_eq(ossl_tolower(case_change[n].l), case_change[n].l);
}

int setup_tests(void)
{
    ADD_ALL_TESTS(test_ctype_chars, 256);
    ADD_ALL_TESTS(test_ctype_negative, 128);
    ADD_ALL_TESTS(test_ctype_toupper, OSSL_NELEM(case_change));
    ADD_ALL_TESTS(test_ctype_tolower, OSSL_NELEM(case_change));
    return 1;
}
