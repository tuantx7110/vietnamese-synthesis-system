/*
 * psola_utils.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: Administrator
 */

#include "psola_utils.h"

void get_max_negative_value(char * signal, int len, int &smax_n){
	smax_n = 0;
	int temp;
	for(int i = 0; i < len; i += 2){
		temp = *(short *)(signal + i);
		smax_n = min(smax_n, temp);
	}
}

void get_max_positive_value(char * signal, int len, int &smax_p){
	smax_p = 0;
	int temp;
	for(int i = 0; i < len; i += 2){
		temp = *(short *)(signal + i);
		smax_p = max(smax_p, temp);
	}
}

void change_amplitude(char * signal, int len, double dcoef){
	int temp;
	for(int i = 0; i < len; i += 2){
		temp = (int)((*(short *)(signal + i)) * dcoef);
		if(temp >= (1 << 15)){
			temp = (1 << 15) - 1;
		}
		if(temp <= -(1 << 15)){
			temp = -(1 << 15);
		}
		*(short *)(signal + i) = (short)(temp);
	}
}

int get_max_to(int * array, int len){
	int Max = 0;
	for(int i = 1; i < len; i ++){
		Max = max(Max, array[i] - array[i - 1]);
	}
	return Max;
}

void hanning_window(char * signal, int len){
	for(int i = 0; i < len; i += 2){
		*(short *)(signal + i) = (short)((*(short *)(signal + i)) * (1 + cos(PI * i * 2/ len - PI)) / 2);
	}
}

int get_average_to(int *a, int number){
	if(number <= 1) return 0;
	int sum = 0;
	for(int i = 0; i < number; i++){
		sum += a[i] - a[i - 1];
	}
	return sum / (number - 1);
}

int get_max_abs_value(short *a, int number){
	int res = 0;
	for(int i = 0; i < number; i++){
		res = max(res, (int) abs(a[i]));
	}
	return res;
}

int rounding(float f){
	int res = int(f);
	if(f >= res + 0.5) res++;
	return res;
}

int get_min_value(int *a, int number){
	if(number <= 0) return -1;
	int res = 1000000005;
	for(int i = 0; i < number; i++) if(res > a[i]){
		res = a[i];
	}
	return res;
}
