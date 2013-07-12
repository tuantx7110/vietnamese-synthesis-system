/*
 * File:   binary_database_converter.h
 * Author: quangpham
 *
 * Created on June 13, 2013, 9:05 PM
 */

#ifndef BINARY_DATABASE_CONVERTER_H
#define	BINARY_DATABASE_CONVERTER_H

#include "xml_database_reader.h"
#include "../encoding/binary_file_writer.h"
#include "../utils/constants.h"

class BinaryDatabaseConverter {
public:
    BinaryDatabaseConverter();
    BinaryDatabaseConverter(string output_binary_file);
    virtual ~BinaryDatabaseConverter();

    bool convertXmlDatabase(XmlDatabaseReader xml_database_reader);
    bool convertXmlDatabase(vector<RecordedSentence>& all_sentences);

private:
    BinaryFileWriter database_writer;
};

#endif	/* BINARY_DATABASE_CONVERTER_H */
