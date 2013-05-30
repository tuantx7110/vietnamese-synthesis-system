/*
 * searching_phrase.h
 *
 *  Created on: May 30, 2013
 *      Author: quangpham
 */

#include <string>
#include <vector>

using namespace std;

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

    void set_phrase_content(string phrase_content);
    string get_phrase_content() const;
    void set_phrase_level(int phrase_level);
    int get_phrase_level() const;
    void set_found(bool found);
    bool is_found() const;
    void set_found_at_syllable(int found_at_syllable);
    int get_found_at_syllable() const;
    void set_found_at_phrase(int found_at_phrase);
    int get_found_at_phrase() const;
    void set_found_at_sentence(int found_at_sentence);
    int get_found_at_sentence() const;

private:
    string phrase_content;
    int phrase_level;
    vector<SearchingPhrase> sub_phrases;

    bool found;
    int found_at_sentence;
    int found_at_phrase;
    int found_at_syllable;
};

#endif /* SEARCHING_PHRASE_H_ */
