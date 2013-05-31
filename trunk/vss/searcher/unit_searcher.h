/*
 * unit_searcher.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "../units/searching_sentence.h"
#include "../units/searching_phrase.h"
#include "../units/recorded_sentence.h"
#include "../units/recorded_phrase.h"
#include "../units/recorded_syllable.h"

#ifndef UNIT_SEARCHER_H_
#define UNIT_SEARCHER_H_

#define debug_unit_searcher 1

class UnitSearcher {
public:
    UnitSearcher();
    virtual ~UnitSearcher();

    bool init();
    vector<SearchingSentence> search(vector<SearchingSentence>& all_searching_sentences, vector<RecordedSentence>& all_recorded_sentences);

private:
    SearchingSentence search_sentence(vector<SearchingPhrase>& all_searching_phrases, vector<RecordedSentence>& all_recorded_sentences);
    void search_phrase(SearchingPhrase& searching_phrase, vector<RecordedSentence>& all_recorded_sentences);
};

#endif /* UNIT_SEARCHER_H_ */
