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
    if (!binary_database_reader.load_data()) {
        cerr << "Cannot load recorded database description" << endl;
        return false;
    }
    if (!unit_searcher.init()) {
        cerr << "Cannot initialize unit searcher" << endl;
        return false;
    }
    return true;
}

vector<SearchingSentence>& UnitSelector::select(vector<SearchingSentence>& input_sentences) {
    time_t start_time = clock();
    time_t current_time = clock();

    search_result = unit_searcher.search(input_sentences, binary_database_reader.get_all_sentences());

    if (debug_unit_selector) {
        current_time = clock();
        cout << "=== SEARCH TIME: " << ((current_time - start_time) * 1000.0 / CLOCKS_PER_SEC) << " ms ===" << endl << endl;
        start_time = current_time;
    }

    for (int i = 0; i < (int) search_result.size(); ++i) {
        select_sentence(search_result[i]);
    }

    if (debug_unit_selector) {
        current_time = clock();
        cout << "=== SELECT TIME: " << ((current_time - start_time) * 1000.0 / CLOCKS_PER_SEC) << " ms ===" << endl << endl;
        start_time = current_time;
    }

    return search_result;
}

void UnitSelector::select_sentence(SearchingSentence& searching_sentence) {
    calculate_score(searching_sentence);
    find_best_path(searching_sentence);
}

void UnitSelector::calculate_score(SearchingSentence& searching_sentence) {
    vector<SearchingPhrase>& phrases = searching_sentence.get_searching_phrases();
    for (int i = 0; i < (int) phrases.size(); ++i) {
        phrases[i].set_n(phrases[i].is_found() ? phrases[i].number_candidates() : 1);
    }

    for (int i1 = 0, i2 = i1 + 1; i2 < (int) phrases.size(); ++i1, i2 = i1 + 1) {
        int n1 = phrases[i1].get_n();
        int n2 = phrases[i2].get_n();
        phrases[i1].create_score_matrix(n1, n2);

        if (phrases[i1].is_found() && phrases[i2].is_found()) {
            for (int j1 = 0; j1 < n1; ++j1) {
                FoundPosition position1 = phrases[i1].get_found_position(j1);
                for (int j2 = 0; j2 < n2; ++j2) {
                    FoundPosition position2 = phrases[i2].get_found_position(j2);
                    int score = score_between_two_candidate_positions(position1, position2);
                    phrases[i1].set_score_at(j1, j2, score);
                }
            }
        } else {
            // TODO
        }
    }
}

int UnitSelector::score_between_two_candidate_positions(FoundPosition position1, FoundPosition position2) {
    if (position1.get_sentence_index() == position2.get_sentence_index() &&
            position1.get_phrase_index() == position2.get_phrase_index() &&
            position1.get_finish_syllable_index() + 1 == position2.get_start_syllable_index()) {
        return 0;
    }
    RecordedPhrase phrase1 = binary_database_reader.get_sentence_at(position1.get_sentence_index()).get_phrase_at(position1.get_phrase_index());
    RecordedPhrase phrase2 = binary_database_reader.get_sentence_at(position2.get_sentence_index()).get_phrase_at(position2.get_phrase_index());

    RecordedSyllable syllable1 = phrase1.get_syllable_at(position1.get_finish_syllable_index());
    RecordedSyllable syllable2 = phrase2.get_syllable_at(position2.get_start_syllable_index());

    RecordedSyllable right_syllable1;
    right_syllable1.set_syllable_tone(syllable1.get_right_syllable_tone());
    right_syllable1.set_initial_phoneme(syllable1.get_right_syllable_initial_phoneme());
    right_syllable1.set_initial_phoneme_type(syllable1.get_right_syllable_phoneme_type());
    right_syllable1.set_syllable_name(syllable1.get_right_syllable_name());

    RecordedSyllable left_syllable2;
    left_syllable2.set_syllable_tone(syllable2.get_left_syllable_tone());
    left_syllable2.set_final_phoneme(syllable2.get_left_syllable_final_phoneme());
    left_syllable2.set_final_phoneme_type(syllable2.get_left_syllable_phoneme_type());
    left_syllable2.set_syllable_name(syllable2.get_left_syllable_name());

    int score1 = score_between_two_syllables(syllable1, left_syllable2, true);
    int score2 = score_between_two_syllables(syllable2, right_syllable1, false);
    return score1 + score2;
}

int UnitSelector::score_between_two_syllables(RecordedSyllable syllable1, RecordedSyllable syllable2, bool left_candidate) {
    if (syllable1.get_syllable_name() == syllable2.get_syllable_name()) {
        return 1;
    }

    int score1 = 0;
    int score2 = 0;
    int score3 = score_between_two_tones(syllable1.get_syllable_tone(), syllable2.get_syllable_tone());

    if (left_candidate) {
        score1 = (syllable1.get_final_phoneme() == syllable2.get_final_phoneme()) ? 100 : 1000;
        score2 = (syllable1.get_final_phoneme_type() == syllable2.get_final_phoneme_type()) ? 100 : 1000;
    } else {
        score1 = (syllable1.get_initial_phoneme() == syllable2.get_initial_phoneme()) ? 100 : 1000;
        score2 = (syllable1.get_initial_phoneme_type() == syllable2.get_initial_phoneme_type()) ? 100 : 1000;
    }

    return 700 * score1 + 500 * score2 + 800 * score3;
}

int UnitSelector::score_between_two_tones(int tone1, int tone2) {
    if (tone1 == tone2 || (tone1 == 0 && tone2 == 1) || (tone1 == 1 && tone2 == 0)) {
        return 1;
    }
    const int d1[] = {0, 0, -1, 1, -1, 1, -1, 1, -1};
    const int d2[] = {0, 0, 1, 4, 2, 1, 6, 1, 1};
    return 100 * abs(d1[tone1] - d1[tone2]) + 100 * (d2[tone1] + d2[tone2]);
}

void UnitSelector::find_best_path(SearchingSentence& searching_sentence) {
    const int infinite = 100000000;
    vector<SearchingPhrase>& phrases = searching_sentence.get_searching_phrases();

    phrases[0].create_dp(0);
    for (int i = 1; i < (int) phrases.size(); ++i) {
        phrases[i].create_dp(infinite);
        for (int j = 0; j < phrases[i].get_n(); ++j) {
            for (int k = 0; k < phrases[i - 1].get_n(); ++k) {
                int score = phrases[i - 1].get_dp(k) + phrases[i - 1].get_score_at(k, j);
                if (phrases[i].get_dp(j) > score) {
                    phrases[i].set_dp(j, score);
                    phrases[i].set_trace(j, k);
                }
            }
        }
    }

    int best_score = infinite;
    int chose = -1;

    int i = (int) phrases.size() - 1;
    for (int j = 0; j < phrases[i].get_n(); ++j) {
        if (best_score > phrases[i].get_dp(j)) {
            best_score = phrases[i].get_dp(j);
            chose = j;
        }
    }

    if (debug_unit_selector) {
        cout << "Sentence: " << searching_sentence.get_sentence_content() << endl;
        cout << "Best score = " << best_score << endl;
    }

    while (i >= 0) {
        if (phrases[i].is_found()) {
            FoundPosition position = phrases[i].get_found_position(chose);
            RecordedPhrase chose_phrase = binary_database_reader.get_sentence_at(position.get_sentence_index()).get_phrase_at(position.get_phrase_index());
            phrases[i].set_chose_candidate(chose);
            phrases[i].set_chose_file_name(binary_database_reader.get_sentence_at(position.get_sentence_index()).get_file_name());
            phrases[i].set_chose_start(chose_phrase.get_syllable_at(position.get_start_syllable_index()).get_start_index());
            phrases[i].set_chose_finish(chose_phrase.get_syllable_at(position.get_finish_syllable_index()).get_finish_index());
        }
        chose = phrases[i].get_trace(chose);
        i = i - 1;
    }

    if (debug_unit_selector) {
        for (int i = 0; i < (int) phrases.size(); ++i) {
            cout << "  " << phrases[i].get_phrase_content() << " ";
            if (phrases[i].is_found()) {
                cout << phrases[i].get_chose_file_name() << " " << phrases[i].get_chose_start() << " " << phrases[i].get_chose_finish() << endl;
            } else {
                cout << "not found" << endl;
            }
        }
        cout << endl;
    }
}
