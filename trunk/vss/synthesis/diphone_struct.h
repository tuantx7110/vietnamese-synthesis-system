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

struct diphone{
	char * buffer;
	int * pitch_marks;
	short tran_point;
	int dw_diplen;
	int num_pitch_marks;
};

struct phone{
	char * buffer;
	int buffer_max;
	int phone_len;
	int handle_len;
	int handle_point;
	int new_handle_len;
	char *phone;
	float f_transition_point;
};

struct frame_position{
	int start_point;
	int signal_len;
	int *position;
	int count;
	int number_position;
	int addition;
	int trans_point;
};

struct syllable{
	string left_diphone_name, right_diphone_name;
	char * new_syllable;
	int syllable_len;
	int tone;
	int energy;
	int number_f0;
	int *f0;
	syllable(){};
	syllable(string _left_diphone_name,string _right_diphone_name, int _syllable_len, int _tone,
			int _energy, int _number_f0){
		left_diphone_name = _left_diphone_name;
		right_diphone_name = _right_diphone_name;
		syllable_len = _syllable_len;
		tone = _tone;
		energy = _energy;
		number_f0 = _number_f0;
	}
};
