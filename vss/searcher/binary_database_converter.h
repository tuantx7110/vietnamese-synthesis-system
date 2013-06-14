/*
 * File:   binary_database_converter.h
 * Author: quangpham
 *
 * Created on June 13, 2013, 9:05 PM
 */

#ifndef BINARY_DATABASE_CONVERTER_H
#define	BINARY_DATABASE_CONVERTER_H

#include "recorded_database_reader.h"
#include "../encoding/binary_file_writer.h"
#include "../utils/constants.h"

class BinaryDatabaseConverter {
public:
    BinaryDatabaseConverter();
    virtual ~BinaryDatabaseConverter();

    void convert_to_binary();

private:
    RecordedDatabaseReader database_reader;
    BinaryFileWriter database_writer;
};

#endif	/* BINARY_DATABASE_CONVERTER_H */
