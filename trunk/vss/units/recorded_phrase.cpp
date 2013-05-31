/*
 * recorded_phrase.cpp
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include "recorded_phrase.h"

RecordedPhrase::RecordedPhrase() {
    init();
}

RecordedPhrase::~RecordedPhrase() {
    // TODO Auto-generated destructor stub
}

void RecordedPhrase::init() {
    phrase_id = -1;
    phrase_length = -1;
    phrase_content = "";
    syllables.clear();
}

void RecordedPhrase::set_phrase_length(int phrase_length) {
    this->phrase_length = phrase_length;
}

int RecordedPhrase::get_phrase_length() const {
    return phrase_length;
}

void RecordedPhrase::set_phrase_id(int phrase_id) {
    this->phrase_id = phrase_id;
}

int RecordedPhrase::get_phrase_id() const {
    return phrase_id;
}

string RecordedPhrase::get_phrase_content() {
    if (phrase_content.length() == 0) {
        phrase_content = "";
        for (int i = 0; i < (int) syllables.size(); ++i) {
            phrase_content = phrase_content + " " + syllables[i].get_syllable_name();
        }
        trim_string(phrase_content);
    }
    return phrase_content;
}

void RecordedPhrase::add_syllable(RecordedSyllable syllable) {
    syllables.push_back(syllable);
}

vector<RecordedSyllable>& RecordedPhrase::get_all_syllables() {
    return syllables;
}

RecordedSyllable& RecordedPhrase::get_syllable_at(int index) {
    return syllables[index];
}

int RecordedPhrase::number_syllables() {
    return syllables.size();
}