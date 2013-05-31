/*
 * unit_selector.cpp
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#include "unit_selector.h"

UnitSelector::UnitSelector() {
    // TODO Auto-generated constructor stub
}

UnitSelector::~UnitSelector() {
    // TODO Auto-generated destructor stub
}

bool UnitSelector::init() {
    if (!recorded_database_reader.load_data()) {
        cerr << "Cannot load recorded database description" << endl;
        return false;
    }
    if (!unit_searcher.init()) {
        cerr << "Cannot initialize unit searcher" << endl;
        return false;
    }
    return true;
}

vector<SearchingSentence> UnitSelector::select(vector<SearchingSentence>& input_sentences) {
    search_result = unit_searcher.search(input_sentences, recorded_database_reader.get_all_sentences());
    calculate_score();
    find_best_path();
    return search_result;
}

void UnitSelector::calculate_score() {

}

void UnitSelector::find_best_path() {

}
