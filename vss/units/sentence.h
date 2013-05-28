/*
 * sentence.h
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include <string>
#include <vector>

using namespace std;

#include "phrase.h"

#ifndef SENTENCE_H_
#define SENTENCE_H_

class Sentence {
public:
    Sentence();
    virtual ~Sentence();

    void init();
    void set_sentence_content(string sentence_content);
    string get_sentence_content() const;
    void set_sentence_id(int sentence_id);
    int get_sentence_id() const;
    void set_file_name(string file_name);
    string get_file_name() const;
    void set_file_id(int file_id);
    int get_file_id() const;

    void add_phrase(Phrase phrase);

private:
    int file_id;
    string file_name;
    int sentence_id;
    string sentence_content;
    vector<Phrase> phrases;
};

#endif /* SENTENCE_H_ */
