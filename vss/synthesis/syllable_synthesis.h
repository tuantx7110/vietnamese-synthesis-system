#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <cstdio>
#include <sstream>
#include <iostream>
#include "../utils/wave_file.h"
#include "../parser/char_codec.h"

using namespace std;

struct syllable{
	syllable(){};
	syllable(string _left_diphone_name,string _right_diphone_name){
		left_diphone_name = _left_diphone_name;
		right_diphone_name = _right_diphone_name;
	}
	string left_diphone_name, right_diphone_name;
};

struct synthesis{
	map<string, syllable> syllable_map;
	map<string, int> phone_map;
	map<wchar_t, pair<wchar_t, int> > tone_map;
	map<string, int> diphone_map;
	void init();
	void read_diphone_binary();
	void read_syllable_diphone();
	void read_vowel_tone();
	WaveFile create_wave_file(string in);
	void add_data(WaveFile &W, int pos);
	int cut_tone(string &in);
};
