/*
 * unit_searcher.cpp
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include "unit_searcher.h"

UnitSearcher::UnitSearcher() {
    // TODO Auto-generated constructor stub

}

UnitSearcher::~UnitSearcher() {
    // TODO Auto-generated destructor stub
}

bool UnitSearcher::init() {
    return true;
}

bool UnitSearcher::search_units_in_recorded_database(RecordedDatabaseReader& recorded_database_reader, InputTextReader& input_text_reader) {
    vector<Sentence>& all_recorded_sentences = recorded_database_reader.get_all_sentences();
    vector<SearchingSentence>& all_searching_sentences = input_text_reader.get_all_searching_sentences();

    for (int i = 0; i < (int) all_searching_sentences.size(); ++i) {
        SearchingSentence searching_sentence = all_searching_sentences[i];
        
    }

    return true;
}
