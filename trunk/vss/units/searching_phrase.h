/*
 * searching_phrase.h
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include <string>
#include <vector>

using namespace std;

#include "../searcher/found_position.h"

#ifndef SEARCHING_PHRASE_H_
#define SEARCHING_PHRASE_H_

class SearchingPhrase {
public:
    SearchingPhrase();
    virtual ~SearchingPhrase();

    void init();
    void add_sub_phrase(SearchingPhrase sub_phrase);
    bool has_sub_phrase();
    vector<SearchingPhrase>& get_sub_phrases();
    int number_sub_phrases();
    int number_candidates();
    void add_found_position(FoundPosition position);
    FoundPosition get_found_position(int i) const;
    void create_score_matrix(int n1, int n2);
    void set_score_at(int i1, int i2, int value);
    int get_score_at(int i1, int i2) const;
    void create_dp(int init_value);
    void set_dp(int i, int value);
    int get_dp(int i) const;
    void set_trace(int i, int value);
    int get_trace(int i) const;


    void set_phrase_content(string phrase_content);
    string get_phrase_content() const;
    void set_phrase_level(int phrase_level);
    int get_phrase_level() const;
    void set_found(bool found);
    bool is_found() const;
    int get_n1() const;
    int get_n2() const;
    void set_n(int n);
    int get_n() const;
    void set_chose_finish(int chose_finish);
    int get_chose_finish() const;
    void set_chose_start(int chose_start);
    int get_chose_start() const;
    void set_chose_file_name(string chose_file_name);
    string get_chose_file_name() const;
    void set_chose_candidate(int chose_candidate);
    int get_chose_candidate() const;

private:
    string phrase_content;
    int phrase_level;
    vector<SearchingPhrase> sub_phrases;

    bool found;
    vector<FoundPosition> found_positions;

    int n1;
    int n2;
    vector< vector<int> > score;

    int n;
    vector<int> dp;
    vector<int> trace;

    int chose_candidate;
    string chose_file_name;
    int chose_start;
    int chose_finish;
};

#endif /* SEARCHING_PHRASE_H_ */
