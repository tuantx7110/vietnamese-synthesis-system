/*
 * phrase.h
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include <vector>
using namespace std;

#include "syllable.h"

#ifndef PHRASE_H_
#define PHRASE_H_

class Phrase {
public:
    Phrase();
    virtual ~Phrase();

    void init();
    void set_phrase_length(int phrase_length);
    int get_phrase_length() const;
    void set_phrase_id(int phrase_id);
    int get_phrase_id() const;

    void add_syllable(Syllable syllable);

private:
    int phrase_id;
    int phrase_length;
    vector<Syllable> syllables;
};

#endif /* PHRASE_H_ */
