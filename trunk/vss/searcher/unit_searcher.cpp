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

vector<SearchingSentence> UnitSearcher::search(vector<SearchingSentence>& all_searching_sentences, vector<RecordedSentence>& all_recorded_sentences) {
    vector<SearchingSentence> result;

    for (int i = 0; i < (int) all_searching_sentences.size(); ++i) {
        result.push_back(search_sentence(all_searching_sentences[i].get_searching_phrases(), all_recorded_sentences));
    }

    if (debug_unit_searcher) {
        for (int i = 0; i < (int) result.size(); ++i) {
            vector<SearchingPhrase> phrases = result[i].get_searching_phrases();
            cout << "Sentence " << (i + 1) << endl;
            for (int j = 0; j < (int) phrases.size(); ++j) {
                cout << "  Phrase \"" << phrases[j].get_phrase_content() << "\" [level " << phrases[j].get_phrase_level() << "] is ";
                if (phrases[j].is_found()) cout << " found" << endl;
                else cout << "not found" << endl;
            }
        }
    }

    return result;
}

SearchingSentence UnitSearcher::search_sentence(vector<SearchingPhrase>& all_searching_phrases, vector<RecordedSentence>& all_recorded_sentences) {
    SearchingSentence result;

    for (int i = 0; i < (int) all_searching_phrases.size(); ++i) {
        search_phrase(all_searching_phrases[i], all_recorded_sentences);

        if (all_searching_phrases[i].is_found()) {
            result.add_searching_phrase(all_searching_phrases[i]);
            continue;
        }

        if (!all_searching_phrases[i].has_sub_phrase()) {
            result.add_searching_phrase(all_searching_phrases[i]);
            continue;
        }

        vector<SearchingPhrase>& sub_phrases = all_searching_phrases[i].get_sub_phrases();
        for (int j = 0; j < (int) sub_phrases.size(); ++j) {
            search_phrase(sub_phrases[j], all_recorded_sentences);
            result.add_searching_phrase(sub_phrases[j]);
        }
    }

    return result;
}

void UnitSearcher::search_phrase(SearchingPhrase& searching_phrase, vector<RecordedSentence>& all_recorded_sentences) {
    if (searching_phrase.get_phrase_content() == "SIL" || searching_phrase.get_phrase_content() == "SILS") {
        return;
    }
    for (int i = 0; i < (int) all_recorded_sentences.size(); ++i) {
        vector<RecordedPhrase>& recorded_phrases = all_recorded_sentences[i].get_all_phrases();

        for (int j = 0; j < (int) recorded_phrases.size(); ++j) {
            vector<RecordedSyllable>& recorded_syllables = recorded_phrases[j].get_all_syllables();
            int number_syllables = (int) recorded_syllables.size();

            if (!searching_phrase.has_sub_phrase()) {
                for (int k = 0; k < number_syllables; ++k) {
                    if (searching_phrase.get_phrase_content() == recorded_syllables[k].get_syllable_name()) {
                        searching_phrase.set_found(true);

                        if (searching_phrase.number_candidates() >= 15) return;
                        searching_phrase.add_found_position(FoundPosition(i, j, k, k));

                        if (debug_unit_searcher) {
                            cout << "Found phrase \"" << searching_phrase.get_phrase_content() << "\" at " << i << " " << j << " " << k << endl;
                            cout << all_recorded_sentences[i].get_all_phrases()[j].get_phrase_content() << endl << endl;
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
                        searching_phrase.add_found_position(FoundPosition(i, j, k, k + number_sub_phrases - 1));

                        if (debug_unit_searcher) {
                            cout << "Found phrase \"" << searching_phrase.get_phrase_content() << "\" at " << i << " " << j << " " << k << " " << (k + number_sub_phrases - 1) << endl;
                            cout << all_recorded_sentences[i].get_all_phrases()[j].get_phrase_content() << endl << endl;
                        }
                    }
                }
            }
        }
    }
}
