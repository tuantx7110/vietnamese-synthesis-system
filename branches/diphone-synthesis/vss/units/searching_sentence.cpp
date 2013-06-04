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

vector<SearchingPhrase>& SearchingSentence::get_searching_phrases() {
    return searching_phrases;
}

string SearchingSentence::get_sentence_content() {
    if (sentence_content.length() == 0) {
        sentence_content = "";
        for (int i = 0; i < (int) searching_phrases.size(); ++i) {
            sentence_content = sentence_content + " " + searching_phrases[i].get_phrase_content();
        }
        trim_string(sentence_content);
    }
    return sentence_content;
}
