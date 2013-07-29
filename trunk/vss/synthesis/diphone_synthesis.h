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
#include "../utils/psola_utils.h"


struct psola{
	bool create_phone(diphone dip1, diphone dip2, phone &P, int * frame_position, int number_frames);
	int tone_for_syllable(int tone_type, int F0, int **f0, int **len, int len_of_syllable, float f_transition_point);
	bool accent_from_phone(diphone dip1, diphone dip2, phone &P, int *f0, int number_f0, int tone_type);
	int sans_accent_from_phone(frame_position &st_frame_position, int new_to);
	int accent_grave_from_phone(frame_position &st_frame_position, int start_to, int finish_to);
	int accent_aigu_from_phone(frame_position &st_frame_position, int start_to, int finish_to);
	WaveFile create_syllable(syllable syl, diphone dip1, diphone dip2);
};
