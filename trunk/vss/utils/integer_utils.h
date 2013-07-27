/*
 * File:   integer_utils.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:25 AM
 */

#ifndef INTEGER_UTILS_H
#define	INTEGER_UTILS_H

#include <string>
#include "data_types.h"
#include "constants.h"

using namespace std;

word mask(int number_bits);
int bit_at(word number, int i);
string binary_reversed(word number, int length = kWordSize);

#endif	/* INTEGER_UTILS_H */

