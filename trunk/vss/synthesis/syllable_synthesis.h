#include "diphone_synthesis.h"

struct synthesis{
	map<string, syllable> syllable_map;
	map<string, int> phone_map;
	map<string, int> diphone_map;
	void init();
	void read_diphone_binary();
	void read_syllable_diphone();
	void read_vowel_tone();
	WaveFile create_wave_file(string in);
	void add_data(WaveFile &W, int pos);
	int cut_tone(string &in);
	diphone get_diphone(string in);
};

