/*
 * unit_selector.h
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#ifndef UNIT_SELECTOR_H_
#define UNIT_SELECTOR_H_

#include <cstdlib>
#include "binary_database_reader.h"
#include "unit_searcher.h"

#define debug_unit_selector 1

class UnitSelector {
public:
    UnitSelector();
    virtual ~UnitSelector();

    bool init();
    vector<SearchingSentence>& select(vector<SearchingSentence>& input_sentences);

private:
    BinaryDatabaseReader binary_database_reader;
    UnitSearcher unit_searcher;
    vector<SearchingSentence> search_result;

    void select_sentence(SearchingSentence& searching_sentence);
    void calculate_score(SearchingSentence& searching_sentence);
    void find_best_path(SearchingSentence& searching_sentence);
    int score_between_two_candidate_positions(FoundPosition position1, FoundPosition position2);
    int score_between_two_syllables(RecordedSyllable syllable1, RecordedSyllable syllable2, bool left_candidate);
    int score_between_two_tones(int tone1, int tone2);
};

#endif /* UNIT_SELECTOR_H_ */
