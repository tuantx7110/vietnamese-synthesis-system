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
    if (!recorded_database_reader.load_data()) {
        cerr << "Cannot load recorded database description" << endl;
        return false;
    }
    return true;
}

void UnitSearcher::search(vector<SearchingSentence>& all_searching_sentences) {
    for (int i = 0; i < (int) all_searching_sentences.size(); ++i) {
        search_sentence(all_searching_sentences[i]);
    }
}

void UnitSearcher::search_sentence(SearchingSentence& searching_sentence) {
    vector<SearchingPhrase>& all_searching_phrases = searching_sentence.get_searching_phrases();

    for (int i = 0; i < (int) all_searching_phrases.size(); ++i) {
        search_phrase(all_searching_phrases[i]);

        if (!all_searching_phrases[i].is_found()) {
            vector<SearchingPhrase>& sub_phrases = all_searching_phrases[i].get_sub_phrases();

            for (int j = 0; j < (int) sub_phrases.size(); ++j) {
                search_phrase(sub_phrases[j]);
            }
        }
    }
}

void UnitSearcher::search_phrase(SearchingPhrase& searching_phrase) {
    vector<RecordedSentence>& all_recorded_sentences = recorded_database_reader.get_all_sentences();

    for (int i = 0; i < (int) all_recorded_sentences.size(); ++i) {
        vector<RecordedPhrase>& recorded_phrases = all_recorded_sentences[i].get_all_phrases();

        for (int j = 0; j < (int) recorded_phrases.size(); ++j) {
            vector<RecordedSyllable>& recorded_syllables = recorded_phrases[j].get_all_syllables();
            int number_syllables = (int) recorded_syllables.size();

            if (!searching_phrase.has_sub_phrase()) {
                for (int k = 0; k < number_syllables; ++k) {
                    if (searching_phrase.get_phrase_content() == recorded_syllables[k].get_syllable_name()) {
                        searching_phrase.set_found(true);
                        searching_phrase.set_found_at_sentence(i);
                        searching_phrase.set_found_at_phrase(j);
                        searching_phrase.set_found_at_syllable(k);

                        if (debug_unit_searcher) {
                            cout << "Found phrase \"" << searching_phrase.get_phrase_content() << "\" at " << i << " " << j << " " << k << endl;
                            cout << recorded_database_reader.get_all_sentences()[i].get_all_phrases()[j].get_phrase_content() << endl << endl;
                        }
                    }
                }
            } else {
                vector<SearchingPhrase>& sub_phrases = searching_phrase.get_sub_phrases();
                int number_sub_phrases = (int) sub_phrases.size();

                for (int k = 0; k + number_sub_phrases - 1 < number_syllables; ++k) {
                    bool found = true;
                    for (int pos = 0; pos < number_sub_phrases; ++pos) {
                        if (sub_phrases[pos].get_phrase_content() != recorded_syllables[k + pos].get_syllable_name()) {
                            found = false;
                            break;
                        }
                    }

                    if (found) {
                        searching_phrase.set_found(true);
                        searching_phrase.set_found_at_sentence(i);
                        searching_phrase.set_found_at_phrase(j);
                        searching_phrase.set_found_at_syllable(k);

                        if (debug_unit_searcher) {
                            cout << "Found phrase \"" << searching_phrase.get_phrase_content() << "\" at " << i << " " << j << " " << k << endl;
                            cout << recorded_database_reader.get_all_sentences()[i].get_all_phrases()[j].get_phrase_content() << endl << endl;
                        }
                    }
                }
            }
        }
    }
}
