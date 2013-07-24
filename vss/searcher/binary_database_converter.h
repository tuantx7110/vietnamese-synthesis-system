/*
 * File:   binary_database_converter.h
 * Author: quangpham
 *
 * Created on June 13, 2013, 9:05 PM
 */

#ifndef BINARY_DATABASE_CONVERTER_H
#define	BINARY_DATABASE_CONVERTER_H

#include <set>
using namespace std;

#include "xml_database_reader.h"
#include "../encoding/binary_file_writer.h"
#include "../utils/constants.h"
#include "../utils/text_file_utils.h"
#include "../utils/string_utils.h"

class BinaryDatabaseConverter {
public:
    BinaryDatabaseConverter();
    virtual ~BinaryDatabaseConverter();

    void convert_to_binary();

private:
    XmlDatabaseReader database_reader;
    BinaryFileWriter database_writer;
    void save_database_statistic(set<string> syllables, int count_syllables, string filename);
};

#endif	/* BINARY_DATABASE_CONVERTER_H */
