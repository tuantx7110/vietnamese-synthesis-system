/*
 * searching_sentence.h
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include <vector>
#include <string>

using namespace std;

#include "searching_phrase.h"
#include "../utils/string_utils.h"

#ifndef SEARCHING_SENTENCE_H_
#define SEARCHING_SENTENCE_H_

class SearchingSentence {
public:
    SearchingSentence();
    virtual ~SearchingSentence();

    void init();
    void add_searching_phrase(SearchingPhrase searching_phrase);
    vector<SearchingPhrase>& get_searching_phrases();
    string get_sentence_content();

private:
    string sentence_content;
    vector<SearchingPhrase> searching_phrases;
};

#endif /* SEARCHING_SENTENCE_H_ */
