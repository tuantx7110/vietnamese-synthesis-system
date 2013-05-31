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
    void add_found_position(FoundPosition position);

    void set_phrase_content(string phrase_content);
    string get_phrase_content() const;
    void set_phrase_level(int phrase_level);
    int get_phrase_level() const;
    void set_found(bool found);
    bool is_found() const;

private:
    string phrase_content;
    int phrase_level;
    vector<SearchingPhrase> sub_phrases;

    bool found;
    vector<FoundPosition> found_positions;
};

#endif /* SEARCHING_PHRASE_H_ */
