/*
 * recorded_sentence.cpp
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include "recorded_sentence.h"

RecordedSentence::RecordedSentence() {
    init();
}

RecordedSentence::~RecordedSentence() {
    phrases.clear();
}

void RecordedSentence::init() {
    file_id = -1;
    file_name = "";
    sentence_id = -1;
    sentence_content = "";
    phrases.clear();
}

string RecordedSentence::get_sentence_content() {
    if (sentence_content.length() == 0) {
        sentence_content = "";
        for (int i = 0; i < (int) phrases.size(); ++i) {
            sentence_content = sentence_content + " " + phrases[i].get_phrase_content();
        }
        trim_string(sentence_content);
    }
    return sentence_content;
}

void RecordedSentence::set_sentence_id(int sentence_id) {
    this->sentence_id = sentence_id;
}

int RecordedSentence::get_sentence_id() const {
    return sentence_id;
}

void RecordedSentence::set_file_name(string file_name) {
    this->file_name = file_name;
}

string RecordedSentence::get_file_name() const {
    return file_name;
}

void RecordedSentence::set_file_id(int file_id) {
    this->file_id = file_id;
}

int RecordedSentence::get_file_id() const {
    return file_id;
}

void RecordedSentence::add_phrase(RecordedPhrase phrase) {
    phrases.push_back(phrase);
}

vector<RecordedPhrase>& RecordedSentence::get_all_phrases() {
    return phrases;
}