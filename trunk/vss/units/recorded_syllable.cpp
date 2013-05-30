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

void RecordedSyllable::set_right_syllable_phoneme_type(string right_syllable_phoneme_type) {
    this->right_syllable_phoneme_type = right_syllable_phoneme_type;
}

string RecordedSyllable::get_right_syllable_phoneme_type() const {
    return right_syllable_phoneme_type;
}

void RecordedSyllable::set_right_syllable_initial_phoneme(string right_syllable_initial_phoneme) {
    this->right_syllable_initial_phoneme = right_syllable_initial_phoneme;
}

string RecordedSyllable::get_right_syllable_initial_phoneme() const {
    return right_syllable_initial_phoneme;
}

void RecordedSyllable::set_right_syllable_tone(int right_syllable_tone) {
    this->right_syllable_tone = right_syllable_tone;
}

int RecordedSyllable::get_right_syllable_tone() const {
    return right_syllable_tone;
}

void RecordedSyllable::set_left_syllable_phoneme_type(string left_syllable_phoneme_type) {
    this->left_syllable_phoneme_type = left_syllable_phoneme_type;
}

string RecordedSyllable::get_left_syllable_phoneme_type() const {
    return left_syllable_phoneme_type;
}

void RecordedSyllable::set_left_syllable_final_phoneme(string left_syllable_final_phoneme) {
    this->left_syllable_final_phoneme = left_syllable_final_phoneme;
}

string RecordedSyllable::get_left_syllable_final_phoneme() const {
    return left_syllable_final_phoneme;
}

void RecordedSyllable::set_left_syllable_tone(int left_syllable_tone) {
    this->left_syllable_tone = left_syllable_tone;
}

int RecordedSyllable::get_left_syllable_tone() const {
    return left_syllable_tone;
}

void RecordedSyllable::set_final_phoneme(string final_phoneme) {
    this->final_phoneme = final_phoneme;
}

string RecordedSyllable::get_final_phoneme() const {
    return final_phoneme;
}

void RecordedSyllable::set_nucleus_phoneme(string nucleus_phoneme) {
    this->nucleus_phoneme = nucleus_phoneme;
}

string RecordedSyllable::get_nucleus_phoneme() const {
    return nucleus_phoneme;
}

void RecordedSyllable::set_middle_phoneme(string middle_phoneme) {
    this->middle_phoneme = middle_phoneme;
}

string RecordedSyllable::get_middle_phoneme() const {
    return middle_phoneme;
}

void RecordedSyllable::set_initial_phoneme(string initial_phoneme) {
    this->initial_phoneme = initial_phoneme;
}

string RecordedSyllable::get_initial_phoneme() const {
    return initial_phoneme;
}

void RecordedSyllable::set_energy(double energy) {
    this->energy = energy;
}

double RecordedSyllable::get_energy() const {
    return energy;
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

void RecordedSyllable::set_syllable_tone(int syllable_tone) {
    this->syllable_tone = syllable_tone;
}

int RecordedSyllable::get_syllable_tone() const {
    return syllable_tone;
}

void RecordedSyllable::set_syllable_name(string syllable_name) {
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

void RecordedSyllable::set_final_phoneme_type(string final_phoneme_type) {
    this->final_phoneme_type = final_phoneme_type;
}

string RecordedSyllable::get_final_phoneme_type() const {
    return final_phoneme_type;
}

void RecordedSyllable::set_nucleus_phoneme_type(string nucleus_phoneme_type) {
    this->nucleus_phoneme_type = nucleus_phoneme_type;
}

string RecordedSyllable::get_nucleus_phoneme_type() const {
    return nucleus_phoneme_type;
}

void RecordedSyllable::set_middle_phoneme_type(string middle_phoneme_type) {
    this->middle_phoneme_type = middle_phoneme_type;
}

string RecordedSyllable::get_middle_phoneme_type() const {
    return middle_phoneme_type;
}

void RecordedSyllable::set_initial_phoneme_type(string initial_phoneme_type) {
    this->initial_phoneme_type = initial_phoneme_type;
}

string RecordedSyllable::get_initial_phoneme_type() const {
    return initial_phoneme_type;
}

