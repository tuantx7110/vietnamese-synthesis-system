/*
 * recorded_phrase.h
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#ifndef RECORDED_PHRASE_H_
#define RECORDED_PHRASE_H_

#include <vector>
#include <string>
#include "recorded_syllable.h"
#include "../utils/string_utils.h"

using namespace std;

class RecordedPhrase {
public:
    RecordedPhrase();
    virtual ~RecordedPhrase();

    void init();
    void set_phrase_length(int phrase_length);
    int get_phrase_length() const;
    void set_phrase_id(int phrase_id);
    int get_phrase_id() const;
    string get_phrase_content();

    void add_syllable(RecordedSyllable syllable);
    vector<RecordedSyllable>& get_all_syllables();
    RecordedSyllable& get_syllable_at(int index);
    int number_syllables();

private:
    int phrase_id;
    int phrase_length;
    string phrase_content;
    vector<RecordedSyllable> syllables;
};

#endif /* RECORDED_PHRASE_H_ */
