/*
 * File:   integer_utils.cpp
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:25 AM
 */

#include "integer_utils.h"

word mask(int number_bits) {
    return (((word) 1) << number_bits) - 1;
}

int bit_at(int number, int i) {
    return (number >> i) & 1;
}

string binary_reversed(word number, int length) {
    string s = "";
    for (int i = 0; i < length; ++i) {
        s += (char) (bit_at(number, i) + '0');
    }
    return s;
}
