/*
 * recorded_syllable.h
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#ifndef RECORDED_SYLLABLE_H_
#define RECORDED_SYLLABLE_H_

#include <string>
#include "../utils/string_utils.h"

using namespace std;

class RecordedSyllable {
public:
    RecordedSyllable();
    virtual ~RecordedSyllable();

    void init();
    void set_right_syllable_initial_phoneme(string right_syllable_initial_phoneme);
    string get_right_syllable_initial_phoneme() const;
    void set_left_syllable_final_phoneme(string left_syllable_final_phoneme);
    string get_left_syllable_final_phoneme() const;
    void set_final_phoneme(string final_phoneme);
    string get_final_phoneme() const;
    void set_initial_phoneme(string initial_phoneme);
    string get_initial_phoneme() const;
    void set_number_phonemes(int number_phonemes);
    int get_number_phonemes() const;
    void set_finish_index(int finish_index);
    int get_finish_index() const;
    void set_start_index(int start_index);
    int get_start_index() const;
    void set_syllable_name(string syllable_name);
    string get_syllable_name() const;
    void set_syllable_id(int syllable_id);
    int get_syllable_id() const;
    void set_right_syllable_name(string right_syllable_name);
    string get_right_syllable_name() const;
    void set_left_syllable_name(string left_syllable_name);
    string get_left_syllable_name() const;

private:
    int syllable_id;
    string syllable_name;
    int start_index;
    int finish_index;
    int number_phonemes;
    string initial_phoneme;
    string final_phoneme;
    string left_syllable_final_phoneme;
    string left_syllable_name;
    string right_syllable_initial_phoneme;
    string right_syllable_name;
};

#endif /* RECORDED_SYLLABLE_H_ */
