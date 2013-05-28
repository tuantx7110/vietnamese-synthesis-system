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

void Phrase::add_syllable(Syllable syllable) {
    syllables.push_back(syllable);
}