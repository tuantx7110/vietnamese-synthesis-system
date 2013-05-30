/*
 * searching_sentence.cpp
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include "searching_sentence.h"

SearchingSentence::SearchingSentence() {
    init();

}

SearchingSentence::~SearchingSentence() {
    // TODO Auto-generated destructor stub
}

void SearchingSentence::init() {
    sentence_content = "";
    searching_phrases.clear();
}

void SearchingSentence::add_searching_phrase(SearchingPhrase searching_phrase) {
    searching_phrases.push_back(searching_phrase);
}

vector<SearchingPhrase> SearchingSentence::get_searching_phrases() const {
    return searching_phrases;
}

void SearchingSentence::set_sentence_content(string sentence_content) {
    this->sentence_content = sentence_content;
}

string SearchingSentence::get_sentence_content() const {
    return sentence_content;
}