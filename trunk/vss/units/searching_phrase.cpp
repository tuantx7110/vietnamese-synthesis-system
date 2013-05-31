/*
 * searching_phrase.cpp
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include "searching_phrase.h"

SearchingPhrase::SearchingPhrase() {
    // TODO Auto-generated constructor stub

}

SearchingPhrase::~SearchingPhrase() {
    // TODO Auto-generated destructor stub
}

void SearchingPhrase::set_phrase_content(string phrase_content) {
    this->phrase_content = phrase_content;
}

string SearchingPhrase::get_phrase_content() const {
    return phrase_content;
}

void SearchingPhrase::init() {
    phrase_content = "";
    phrase_level = -1;
    sub_phrases.clear();

    found = false;
    found_positions.clear();
}

bool SearchingPhrase::has_sub_phrase() {
    return sub_phrases.size() > 0;
}

void SearchingPhrase::add_sub_phrase(SearchingPhrase sub_phrase) {
    sub_phrases.push_back(sub_phrase);
}

void SearchingPhrase::set_phrase_level(int phrase_level) {
    this->phrase_level = phrase_level;
}

int SearchingPhrase::get_phrase_level() const {
    return phrase_level;
}

void SearchingPhrase::set_found(bool found) {
    this->found = found;
}

bool SearchingPhrase::is_found() const {
    return found;
}

vector<SearchingPhrase>& SearchingPhrase::get_sub_phrases() {
    return sub_phrases;
}

int SearchingPhrase::number_sub_phrases() {
    return sub_phrases.size();
}

void SearchingPhrase::add_found_position(FoundPosition position) {
	found_positions.push_back(position);
}

