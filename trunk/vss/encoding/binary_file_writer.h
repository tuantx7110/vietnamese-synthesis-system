/*
 * File:   binary_file_writer.h
 * Author: quangpham
 *
 * Created on June 10, 2013, 10:48 AM
 */

#ifndef BINARY_FILE_WRITER_H
#define	BINARY_FILE_WRITER_H

#include "binary_file.h"

class BinaryFileWriter : public BinaryFile {
public:
    BinaryFileWriter();
    BinaryFileWriter(string file_name);
    ~BinaryFileWriter();

    bool open(string file_name);
    void close();

    bool write_unary(int number);
    bool write_gamma(int number);
    bool write_delta(int number);
    bool write_omega(int number);
    bool write_string(string s);

private:
    void flush_buffer();
    void write_bits(int bit, int length = 1);
    void write_recursive_omega(int number);
};

#endif	/* BINARY_FILE_WRITER_H */
