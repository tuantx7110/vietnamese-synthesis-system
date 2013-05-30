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

    void set_phrase_content(string phrase_content);
    string get_phrase_content() const;

private:
    string phrase_content;
    vector<SearchingPhrase> sub_phrases;
};

#endif /* SEARCHING_PHRASE_H_ */
