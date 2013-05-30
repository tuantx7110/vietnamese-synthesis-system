/*
 * phrase.cpp
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include "phrase.h"

Phrase::Phrase() {
    init();
}

Phrase::~Phrase() {
    // TODO Auto-generated destructor stub
}

void Phrase::init() {
    phrase_id = -1;
    phrase_length = -1;
    phrase_content = "";
    syllables.clear();
}

void Phrase::set_phrase_length(int phrase_length) {
    this->phrase_length = phrase_length;
}

int Phrase::get_phrase_length() const {
    return phrase_length;
}

void Phrase::set_phrase_id(int phrase_id) {
    this->phrase_id = phrase_id;
}

int Phrase::get_phrase_id() const {
    return phrase_id;
}

string Phrase::get_phrase_content() {
    if (phrase_content.length() == 0) {
        phrase_content = "";
        for (int i = 0; i < (int)syllables.size(); ++i) {
            phrase_content = phrase_content + " " + syllables[i].get_syllable_name();
        }
        trim_string(phrase_content);
    }
    return phrase_content;
}

void Phrase::add_syllable(Syllable syllable) {
    syllables.push_back(syllable);
}
