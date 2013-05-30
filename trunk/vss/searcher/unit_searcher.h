/*
 * unit_searcher.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <vector>
#include <string>

using namespace std;

#include "recorded_database_reader.h"
#include "input_text_reader.h"
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
    void search(vector<SearchingSentence>& all_searching_sentences);

private:
    RecordedDatabaseReader recorded_database_reader;

    void search_sentence(SearchingSentence& searching_sentence);
    void search_phrase(SearchingPhrase& searching_phrase);
};

#endif /* UNIT_SEARCHER_H_ */
