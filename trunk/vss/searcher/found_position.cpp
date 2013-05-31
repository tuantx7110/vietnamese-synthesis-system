/*
 * found_position.cpp
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#include "found_position.h"

FoundPosition::FoundPosition() {
    sentence_index = -1;
    phrase_index = -1;
    start_syllable_index = -1;
    finish_syllable_index = -1;
}

FoundPosition::~FoundPosition() {
    // TODO Auto-generated destructor stub
}

int FoundPosition::get_finish_syllable_index() const {
    return finish_syllable_index;
}

int FoundPosition::get_start_syllable_index() const {
    return start_syllable_index;
}

int FoundPosition::get_phrase_index() const {
    return phrase_index;
}

int FoundPosition::get_sentence_index() const {
    return sentence_index;
}

FoundPosition::FoundPosition(int sentence_index, int phrase_index, int start_syllable_index, int finish_syllable_index) {
    this->sentence_index = sentence_index;
    this->phrase_index = phrase_index;
    this->start_syllable_index = start_syllable_index;
    this->finish_syllable_index = finish_syllable_index;
}