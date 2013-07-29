#ifndef PSOLA_UTILS_H
#define PSOLA_UTILS_H

#include "constants.h"
#include <algorithm>

using namespace std;

void get_max_positive_value(char * signal, int len, int &smax_p);
void get_max_negative_value(char * signal, int len, int &smax_n);
int get_max_abs_value(short *a, int number);
void change_amplitude(char * signal, int len, double dcoef);
int get_max_to(int * array, int len);
void hanning_window(char * signal, int len);
int get_average_to(int * a, int number);
int get_min_value(int * a, int number);
int rounding(float f);

#endif
