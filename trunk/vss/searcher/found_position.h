/*
 * found_position.h
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#ifndef FOUND_POSITION_H_
#define FOUND_POSITION_H_

class FoundPosition {
public:
    FoundPosition();
    FoundPosition(int sentence_index, int phrase_index, int start_syllable_index, int finish_syllable_index);
    virtual ~FoundPosition();

    int get_finish_syllable_index() const;
    int get_start_syllable_index() const;
    int get_phrase_index() const;
    int get_sentence_index() const;

private:
    int sentence_index;
    int phrase_index;
    int start_syllable_index;
    int finish_syllable_index;
};

#endif /* FOUND_POSITION_H_ */
