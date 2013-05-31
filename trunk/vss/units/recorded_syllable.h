/*
 * recorded_syllable.h
 *
 *  Created on: May 28, 2013
 *      Author: quangpham
 */

#include <string>
using namespace std;

#ifndef RECORDED_SYLLABLE_H_
#define RECORDED_SYLLABLE_H_

class RecordedSyllable {
public:
    RecordedSyllable();
    virtual ~RecordedSyllable();

    void init();
    void set_right_syllable_phoneme_type(string right_syllable_phoneme_type);
    string get_right_syllable_phoneme_type() const;
    void set_right_syllable_initial_phoneme(string right_syllable_initial_phoneme);
    string get_right_syllable_initial_phoneme() const;
    void set_right_syllable_tone(int right_syllable_tone);
    int get_right_syllable_tone() const;
    void set_left_syllable_phoneme_type(string left_syllable_phoneme_type);
    string get_left_syllable_phoneme_type() const;
    void set_left_syllable_final_phoneme(string left_syllable_final_phoneme);
    string get_left_syllable_final_phoneme() const;
    void set_left_syllable_tone(int left_syllable_tone);
    int get_left_syllable_tone() const;
    void set_final_phoneme(string final_phoneme);
    string get_final_phoneme() const;
    void set_nucleus_phoneme(string nucleus_phoneme);
    string get_nucleus_phoneme() const;
    void set_middle_phoneme(string middle_phoneme);
    string get_middle_phoneme() const;
    void set_initial_phoneme(string initial_phoneme);
    string get_initial_phoneme() const;
    void set_energy(double energy);
    double get_energy() const;
    void set_number_phonemes(int number_phonemes);
    int get_number_phonemes() const;
    void set_finish_index(int finish_index);
    int get_finish_index() const;
    void set_start_index(int start_index);
    int get_start_index() const;
    void set_syllable_tone(int syllable_tone);
    int get_syllable_tone() const;
    void set_syllable_name(string syllable_name);
    string get_syllable_name() const;
    void set_syllable_id(int syllable_id);
    int get_syllable_id() const;
    void set_final_phoneme_type(string final_phoneme_type);
    string get_final_phoneme_type() const;
    void set_nucleus_phoneme_type(string nucleus_phoneme_type);
    string get_nucleus_phoneme_type() const;
    void set_middle_phoneme_type(string middle_phoneme_type);
    string get_middle_phoneme_type() const;
    void set_initial_phoneme_type(string initial_phoneme_type);
    string get_initial_phoneme_type() const;
    void set_right_syllable_name(string right_syllable_name);
    string get_right_syllable_name() const;
    void set_left_syllable_name(string left_syllable_name);
    string get_left_syllable_name() const;

private:
    int syllable_id;
    string syllable_name;
    int syllable_tone;
    int start_index;
    int finish_index;
    int number_phonemes;
    double energy;
    string initial_phoneme;
    string initial_phoneme_type;
    string middle_phoneme;
    string middle_phoneme_type;
    string nucleus_phoneme;
    string nucleus_phoneme_type;
    string final_phoneme;
    string final_phoneme_type;
    int left_syllable_tone;
    string left_syllable_final_phoneme;
    string left_syllable_phoneme_type;
    string left_syllable_name;
    int right_syllable_tone;
    string right_syllable_initial_phoneme;
    string right_syllable_phoneme_type;
    string right_syllable_name;
};

#endif /* RECORDED_SYLLABLE_H_ */
