/*
 * File:   binary_file.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 11:05 AM
 */

#ifndef BINARY_FILE_H
#define	BINARY_FILE_H

#include <string>
#include <cstdio>
#include <iostream>
#include "../parser/char_codec.h"
#include "../utils/data_types.h"
#include "../utils/constants.h"
#include "../utils/integer_utils.h"

using namespace std;

class BinaryFile {
public:
    BinaryFile();
    virtual ~BinaryFile();

    void print_buffer();
    bool is_opened();

protected:
    string file_name;
    FILE *file;
    word buffer[kBufferSize];
    int pointer;
    bool opened;
    CharCodec codec;

    int get_iword();
    int get_ibit();
    int buffer_capacity();
    void error_file_not_opened();
};

#endif	/* BINARY_FILE_H */
