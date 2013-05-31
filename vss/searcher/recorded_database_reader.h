/*
 * File:   recorded_database_reader.h
 * Author: quangpham
 *
 * Created on May 28, 2013, 9:19 AM
 */
#include <string>
#include <vector>

using namespace std;

#include "../units/recorded_sentence.h"
#include "../units/recorded_phrase.h"
#include "../units/recorded_syllable.h"

#define debug_recorded_database_reader 0

#ifndef RECORDED_DATABASE_READER_H
#define	RECORDED_DATABASE_READER_H

class RecordedDatabaseReader {
public:
    static const string kRecordedDatabasePath;
    static const string kRecordedDatabaseDescriptionPath;

    RecordedDatabaseReader();
    virtual ~RecordedDatabaseReader();

    bool load_data();
    vector<RecordedSentence>& get_all_sentences();
    RecordedSentence& get_sentence_at(int index);

private:
    int current_file_id;
    string current_file_name;
    RecordedSentence current_sentence;
    RecordedPhrase current_phrase;
    RecordedSyllable current_syllable;
    vector<RecordedSentence> all_sentences;

    void init();
    bool read_attribute_value(string s, string& value);
    bool read_content_value(string s, string& value);
    bool read_file_details(vector<string> tokens);
    bool read_sentence_details(vector<string> tokens);
    bool read_phrase_details(vector<string> tokens);
    bool read_syllable_details(vector<string> tokens);
    bool read_phoneme_details(vector<string> tokens, string which_phoneme);
    bool read_neighbor_syllable_details(vector<string> tokens, bool is_left_neighbor);
};

#endif	/* RECORDED_DATABASE_READER_H */

