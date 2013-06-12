/*
 * File:   binary_file_reader.cpp
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:09 AM
 */

#include "binary_file_reader.h"

BinaryFileReader::BinaryFileReader() {
}

BinaryFileReader::BinaryFileReader(string file_name) {
    open(file_name);
}

BinaryFileReader::~BinaryFileReader() {
    close();
}

bool BinaryFileReader::open(string file_name) {
    this->file_name = file_name;

    file = fopen(file_name.c_str(), "rb");
    if (file == NULL) {
        cerr << "Cannot open file " << file_name << " for reading" << endl;
        opened = false;
        return false;
    }

    fill_buffer();
    opened = true;

    return true;
}

void BinaryFileReader::close() {
    if (opened) {
        fclose(file);
        opened = false;
    }
}

void BinaryFileReader::fill_buffer() {
    memset(buffer, 0, sizeof (buffer));
    fread(buffer, sizeof (word), kBufferSize, file);
    pointer = 0;
}

int BinaryFileReader::read_bit() {
    if (buffer_capacity() == 0) fill_buffer();
    int bit = bit_at(buffer[get_iword()], get_ibit());
    ++pointer;
    return bit;
}

int BinaryFileReader::read_unary() {
    if (!opened) {
        error_file_not_opened();
        return 0;
    }
    int number = 1;
    while (read_bit() == 0) ++number;
    return number;
}

int BinaryFileReader::read_gamma() {
    if (!opened) {
        error_file_not_opened();
        return 0;
    }

    int n = 0;
    while (read_bit() == 0) ++n;

    return read_binary(n);
}

int BinaryFileReader::read_delta() {
    return read_binary(read_gamma() - 1);
}

int BinaryFileReader::read_omega() {
    int number = 1;
    while (read_bit() == 1) {
        number = read_binary(number);
    }
    return number;
}

int BinaryFileReader::read_binary(int n) {
    int number = 1;
    for (int i = 0; i < n; ++i) {
        number <<= 1;
        number |= read_bit();
    }
    return number;
}
