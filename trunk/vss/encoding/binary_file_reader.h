/*
 * File:   binary_file_reader.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:09 AM
 */

#ifndef BINARY_FILE_READER_H
#define	BINARY_FILE_READER_H

#include "binary_file.h"

class BinaryFileReader : public BinaryFile {
public:
    BinaryFileReader();
    BinaryFileReader(string file_name);
    ~BinaryFileReader();

    bool open(string file_name);
    void close();

    int read_unary();
    int read_gamma();
    int read_delta();
    int read_omega();
    string read_string();

private:
    void fill_buffer();
    int read_bit();
    int read_binary(int n);
};

#endif	/* BINARY_FILE_READER_H */

