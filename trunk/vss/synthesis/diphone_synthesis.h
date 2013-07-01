#include <algorithm>
#include <cmath>
#include <cstring>
#include "../utils/wave_file.h"
#include "../utils/wave_file_utils.h"

#define PI acos(-1)

struct diphone{
	char * buffer;
	int * pitch_marks;
	int dw_diplen;
	int num_pitch_marks;
};

struct phone{
	char * buffer;
	int phone_len;
};

struct psola{
	double volume_amp;
	bool create_phone(diphone dip1, diphone dip2, phone &P, int * frame_position, int number_frames);
	void get_max_positive_value(char * signal, int len, int &smax_p);
	void get_max_negative_value(char * signal, int len, int &smax_n);
	void change_amplitude(char * signal, int len, double dcoef);
	int get_max_to(int * array, int len);
	void hanning_window(char * signal, int len);
};
