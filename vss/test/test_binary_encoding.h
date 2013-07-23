/*
 * File:   test_binary_encoding.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:59 AM
 */

#ifndef TEST_BINARY_ENCODING_H
#define	TEST_BINARY_ENCODING_H

#include <ctime>

#include "../encoding/binary_file_reader.h"
#include "../encoding/binary_file_writer.h"
#include "../utils/constants.h"

#define debug_test_binary_encoding 1

void test_binary_encoding();
void test_unary();
void test_gamma();
void test_delta();
void test_omega();
void test_string();
void test_all();

#endif	/* TEST_BINARY_ENCODING_H */

