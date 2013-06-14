/*
 * File:   binary_file.cpp
 * Author: quangpham
 *
 * Created on June 11, 2013, 11:05 AM
 */

#include "binary_file.h"

BinaryFile::BinaryFile() {
}

BinaryFile::~BinaryFile() {
}

int BinaryFile::get_iword() {
    return pointer >> kLogWord;
}

int BinaryFile::get_ibit() {
    return pointer & (kWordSize - 1);
}

void BinaryFile::print_buffer() {
    int iword = get_iword();
    for (int i = 0; i <= iword; ++i) {
        cout << binary_reversed(buffer[i]);
    }
    cout << endl;
}

bool BinaryFile::is_opened() {
    return opened;
}

void BinaryFile::error_file_not_opened() {
    cerr << "File " << file_name << " is not opened." << endl;
}

int BinaryFile::buffer_capacity() {
    return kTotalBits - pointer;
}
