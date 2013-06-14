/*
 * File:   binary_database_reader.h
 * Author: quangpham
 *
 * Created on June 14, 2013, 9:18 PM
 */

#ifndef BINARY_DATABASE_READER_H
#define	BINARY_DATABASE_READER_H

#include <vector>
#include <string>
#include "../encoding/binary_file_reader.h"
#include "../units/recorded_sentence.h"
#include "../units/recorded_phrase.h"
#include "../units/recorded_syllable.h"
#include "../utils/constants.h"

using namespace std;

class BinaryDatabaseReader {
public:
    BinaryDatabaseReader();
    virtual ~BinaryDatabaseReader();

    bool load_data();
    vector<RecordedSentence>& get_all_sentences();
    RecordedSentence& get_sentence_at(int index);

private:
    BinaryFileReader reader;
    vector<RecordedSentence> all_sentences;
};

#endif	/* BINARY_DATABASE_READER_H */
