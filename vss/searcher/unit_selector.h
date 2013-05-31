/*
 * unit_selector.h
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#include "recorded_database_reader.h"
#include "unit_searcher.h"

#ifndef UNIT_SELECTOR_H_
#define UNIT_SELECTOR_H_

#define debug_unit_selector 1

class UnitSelector {
public:
    UnitSelector();
    virtual ~UnitSelector();

    bool init();
    vector<SearchingSentence> select(vector<SearchingSentence>& input_sentences);

private:
    RecordedDatabaseReader recorded_database_reader;
    UnitSearcher unit_searcher;
    vector<SearchingSentence> search_result;

    void calculate_score();
    void find_best_path();
};

#endif /* UNIT_SELECTOR_H_ */
