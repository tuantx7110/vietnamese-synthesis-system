/*
 * syllable_synthesis_many.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Administrator
 */

#ifndef SYLLABLE_SYNTHESIS_MANY_H_
#define SYLLABLE_SYNTHESIS_MANY_H_

#include "diphone_synthesis.h"

struct synthesis_many {
    vector<WaveFile> vW;
    map<string, syllable> syllable_map;
    map<string, int> phone_map;
    map<string, vector<int> > diphone_map;
    void init();
    void read_diphone_binary();
    void read_syllable_diphone();
    vector<WaveFile> create_wave_file(string in);
    vector<diphone> get_diphone(string in);

};


#endif /* SYLLABLE_SYNTHESIS_MANY_H_ */
