/*
 * File:   xml_database_reader.h
 * Author: quangpham
 *
 * Created on May 28, 2013, 9:19 AM
 */

#ifndef XML_DATABASE_READER_H
#define	XML_DATABASE_READER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../utils/string_utils.h"
#include "../units/recorded_sentence.h"
#include "../units/recorded_phrase.h"
#include "../units/recorded_syllable.h"
#include "../utils/constants.h"

using namespace std;

#define debug_recorded_database_reader 1

class XmlDatabaseReader {
public:
    XmlDatabaseReader();
    XmlDatabaseReader(string xml_database_path);
    virtual ~XmlDatabaseReader();

    bool load_data();
    vector<RecordedSentence>& get_all_sentences();
    RecordedSentence& get_sentence_at(int index);

private:
    string xml_database_path;
    int current_file_id;
    string current_file_name;
    RecordedSentence current_sentence;
    RecordedPhrase current_phrase;
    RecordedSyllable current_syllable;
    vector<RecordedSentence> all_sentences;

    void init(string xml_database_path);
    bool read_attribute_value(string s, string& value);
    bool read_content_value(string s, string& value);
    bool read_file_details(vector<string> tokens);
    bool read_sentence_details(vector<string> tokens);
    bool read_phrase_details(vector<string> tokens);
    bool read_syllable_details(vector<string> tokens);
    bool read_phoneme_details(vector<string> tokens, string which_phoneme);
    bool read_neighbor_syllable_details(vector<string> tokens, bool is_left_neighbor);
};

#endif	/* XML_DATABASE_READER_H */
