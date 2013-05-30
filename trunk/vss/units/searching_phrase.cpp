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

