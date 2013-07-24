#include <algorithm>
#include <cmath>
#include <cstring>
#include "diphone_struct.h"
#include "../utils/constants.h"

#define fo_begin 210
#define Sample_rate 16000
#define volume_amp 5000
#define safe_buffer 20000
#include "../utils/wave_file.h"
#include "../utils/wave_file_utils.h"

#define PI acos(-1)


struct psola{
	int rounding(float f);
	bool create_phone(diphone dip1, diphone dip2, phone &P, int * frame_position, int number_frames);
	void get_max_positive_value(char * signal, int len, int &smax_p);
	void get_max_negative_value(char * signal, int len, int &smax_n);
	int get_max_abs_value(int *a, int number);
	void change_amplitude(char * signal, int len, double dcoef);
	int get_max_to(int * array, int len);
	void hanning_window(char * signal, int len);
	int tone_for_syllable(int tone_type, int F0, int **f0, int **len, int len_of_syllable, float f_transition_point);
	bool accent_from_phone(diphone dip1, diphone dip2, phone &P, int *f0, int number_f0, int tone_type);
	int get_average_to(int * a, int number);
	int sans_accent_from_phone(frame_position &st_frame_position, int new_to);
	int get_min_value(int * a, int number);
	int accent_grave_from_phone(frame_position &st_frame_position, int start_to, int finish_to);
	int accent_aigu_from_phone(frame_position &st_frame_position, int start_to, int finish_to);
	WaveFile create_syllable(syllable syl, diphone dip1, diphone dip2);
};
