/*
 * searching_phrase.cpp
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include "searching_phrase.h"

SearchingPhrase::SearchingPhrase() {
    // TODO Auto-generated constructor stub

}

SearchingPhrase::~SearchingPhrase() {
    // TODO Auto-generated destructor stub
}

void SearchingPhrase::set_phrase_content(string phrase_content) {
    this->phrase_content = phrase_content;
}

string SearchingPhrase::get_phrase_content() const {
    return phrase_content;
}

void SearchingPhrase::init() {
    phrase_content = "";
    phrase_level = -1;
    sub_phrases.clear();

    found = false;
    found_positions.clear();

    n2 = -1;
    n1 = -1;
    score.clear();

    dp.clear();
    trace.clear();
}

bool SearchingPhrase::has_sub_phrase() {
    return sub_phrases.size() > 0;
}

void SearchingPhrase::add_sub_phrase(SearchingPhrase sub_phrase) {
    sub_phrases.push_back(sub_phrase);
}

void SearchingPhrase::set_phrase_level(int phrase_level) {
    this->phrase_level = phrase_level;
}

int SearchingPhrase::get_phrase_level() const {
    return phrase_level;
}

void SearchingPhrase::set_found(bool found) {
    this->found = found;
}

bool SearchingPhrase::is_found() const {
    return found;
}

int SearchingPhrase::get_n1() const {
    return n1;
}

int SearchingPhrase::get_n2() const {
    return n2;
}

void SearchingPhrase::set_n(int n) {
    this->n = n;
}

int SearchingPhrase::get_n() const {
    return n;
}

void SearchingPhrase::set_chose_finish(int chose_finish) {
    this->chose_finish = chose_finish;
}

int SearchingPhrase::get_chose_finish() const {
    return chose_finish;
}

void SearchingPhrase::set_chose_start(int chose_start) {
    this->chose_start = chose_start;
}

int SearchingPhrase::get_chose_start() const {
    return chose_start;
}

void SearchingPhrase::set_chose_file_name(string chose_file_name) {
    this->chose_file_name = chose_file_name;
}

string SearchingPhrase::get_chose_file_name() const {
    return chose_file_name;
}

void SearchingPhrase::set_chose_candidate(int chose_candidate) {
    this->chose_candidate = chose_candidate;
}

int SearchingPhrase::get_chose_candidate() const {
    return chose_candidate;
}

vector<SearchingPhrase>& SearchingPhrase::get_sub_phrases() {
    return sub_phrases;
}

int SearchingPhrase::number_sub_phrases() {
    return sub_phrases.size();
}

int SearchingPhrase::number_candidates() {
    return found_positions.size();
}

void SearchingPhrase::add_found_position(FoundPosition position) {
    found_positions.push_back(position);
}

FoundPosition SearchingPhrase::get_found_position(int i) const {
    return found_positions[i];
}

void SearchingPhrase::create_score_matrix(int n1, int n2) {
    this->n1 = n1;
    this->n2 = n2;
    score.clear();
    score.resize(n1);
    for (int i = 0; i < n1; ++i) {
        score[i].resize(n2, 0);
    }
}

void SearchingPhrase::set_score_at(int i1, int i2, int value) {
    score[i1][i2] = value;
}

int SearchingPhrase::get_score_at(int i1, int i2) const {
    return score[i1][i2];
}

void SearchingPhrase::create_dp(int init_value) {
    dp.clear();
    dp.resize(n, init_value);
    trace.clear();
    trace.resize(n, 0);
}

void SearchingPhrase::set_dp(int i, int value) {
    dp[i] = value;
}

int SearchingPhrase::get_dp(int i) const {
    return dp[i];
}

void SearchingPhrase::set_trace(int i, int value) {
    trace[i] = value;
}

int SearchingPhrase::get_trace(int i) const {
    return trace[i];
}
