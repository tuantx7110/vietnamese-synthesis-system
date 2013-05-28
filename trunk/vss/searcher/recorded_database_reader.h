/*
 * File:   recorded_database_reader.h
 * Author: quangpham
 *
 * Created on May 28, 2013, 9:19 AM
 */
#include <string>
#include <vector>

using namespace std;

#include "../units/sentence.h"
#include "../units/phrase.h"
#include "../units/syllable.h"

#define debug 0

#ifndef RECORDEDDATABASEREADER_H
#define	RECORDEDDATABASEREADER_H

class RecordedDatabaseReader {
public:
    static const string kRecordedDatabasePath;
    static const string kRecordedDatabaseDescriptionPath;

    RecordedDatabaseReader();
    virtual ~RecordedDatabaseReader();

private:
    int current_file_id;
    string current_file_name;
    Sentence current_sentence;
    Phrase current_phrase;
    Syllable current_syllable;
    vector<Sentence> all_sentences;

    void init();
    void load_data();
    bool read_attribute_value(string s, string& value);
    bool read_content_value(string s, string& value);
    bool read_file_details(vector<string> tokens);
    bool read_sentence_details(vector<string> tokens);
    bool read_phrase_details(vector<string> tokens);
    bool read_syllable_details(vector<string> tokens);
    bool read_phoneme_details(vector<string> tokens, string which_phoneme);
    bool read_neighbor_syllable_details(vector<string> tokens, bool is_left_neighbor);
};

#endif	/* RECORDEDDATABASEREADER_H */

