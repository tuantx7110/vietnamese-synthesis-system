/*
 * recorded_syllable.cpp
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include "recorded_syllable.h"

RecordedSyllable::RecordedSyllable() {
    init();
}

RecordedSyllable::~RecordedSyllable() {
    // TODO Auto-generated destructor stub
}

void RecordedSyllable::init() {
    // TODO
}

void RecordedSyllable::set_right_syllable_initial_phoneme(string right_syllable_initial_phoneme) {
    this->right_syllable_initial_phoneme = right_syllable_initial_phoneme;
}

string RecordedSyllable::get_right_syllable_initial_phoneme() const {
    return right_syllable_initial_phoneme;
}

void RecordedSyllable::set_left_syllable_final_phoneme(string left_syllable_final_phoneme) {
    this->left_syllable_final_phoneme = left_syllable_final_phoneme;
}

string RecordedSyllable::get_left_syllable_final_phoneme() const {
    return left_syllable_final_phoneme;
}

void RecordedSyllable::set_final_phoneme(string final_phoneme) {
    this->final_phoneme = final_phoneme;
}

string RecordedSyllable::get_final_phoneme() const {
    return final_phoneme;
}

void RecordedSyllable::set_initial_phoneme(string initial_phoneme) {
    this->initial_phoneme = initial_phoneme;
}

string RecordedSyllable::get_initial_phoneme() const {
    return initial_phoneme;
}

void RecordedSyllable::set_number_phonemes(int number_phonemes) {
    this->number_phonemes = number_phonemes;
}

int RecordedSyllable::get_number_phonemes() const {
    return number_phonemes;
}

void RecordedSyllable::set_finish_index(int finish_index) {
    this->finish_index = finish_index;
}

int RecordedSyllable::get_finish_index() const {
    return finish_index;
}

void RecordedSyllable::set_start_index(int start_index) {
    this->start_index = start_index;
}

int RecordedSyllable::get_start_index() const {
    return start_index;
}

void RecordedSyllable::set_syllable_name(string syllable_name) {
	replace_all(syllable_name, '_', ' ');
    this->syllable_name = syllable_name;
}

string RecordedSyllable::get_syllable_name() const {
    return syllable_name;
}

void RecordedSyllable::set_syllable_id(int syllable_id) {
    this->syllable_id = syllable_id;
}

int RecordedSyllable::get_syllable_id() const {
    return syllable_id;
}

void RecordedSyllable::set_right_syllable_name(string right_syllable_name) {
	replace_all(right_syllable_name, '_', ' ');
    this->right_syllable_name = right_syllable_name;
}

string RecordedSyllable::get_right_syllable_name() const {
    return right_syllable_name;
}

void RecordedSyllable::set_left_syllable_name(string left_syllable_name) {
	replace_all(left_syllable_name, '_', ' ');
    this->left_syllable_name = left_syllable_name;
}

string RecordedSyllable::get_left_syllable_name() const {
    return left_syllable_name;
}

