#include "diphone_synthesis.h"

void psola::get_max_negative_value(char * signal, int len, int &smax_n){
	smax_n = 0;
	int temp;
	for(int i = 0; i < len; i += 2){
		temp = *(short *)(signal + i);
		smax_n = min(smax_n, temp);
	}
}

void psola::get_max_positive_value(char * signal, int len, int &smax_p){
	smax_p = 0;
	int temp;
	for(int i = 0; i < len; i += 2){
		temp = *(short *)(signal + i);
		smax_p = max(smax_p, temp);
	}
}

void psola::change_amplitude(char * signal, int len, double dcoef){
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

int psola::get_max_to(int * array, int len){
	int Max = 0;
	for(int i = 1; i < len; i ++){
		Max = max(Max, array[i] - array[i - 1]);
	}
	return Max;
}

void psola::hanning_window(char * signal, int len){
	for(int i = 0; i < len; i += 2){
		*(short *)(signal + i) = (short)((*(short *)(signal + i)) * (1 + cos(PI * i * 2/ len - PI)) / 2);
	}
}

bool psola::create_phone(diphone dip1, diphone dip2, phone &P, int * frame_position, int number_frames){
	int nearest_peak_index;
	int frame_len;
	int tempt;
	char *cFrame = new char[2];
	char *cFrame2 = new char[2];

	double t1, t2;
	int smax_p1, smax_p2, smax_n1, smax_n2;
	double dstart_coef, dfinish_coef;

	get_max_positive_value(dip1.buffer + dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, dip1.dw_diplen - dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, smax_p1);
	get_max_negative_value(dip1.buffer + dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, dip1.dw_diplen - dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, smax_n1);
	get_max_positive_value(dip2.buffer, dip2.pitch_marks[1] * 2, smax_p2);
	get_max_negative_value(dip2.buffer, dip2.pitch_marks[1] * 2, smax_n2);

	t1 = (smax_p1 - smax_n1) / 2.0;
	t2 = (smax_p2 - smax_n2) / 2.0;

	volume_amp = 5000;
	dstart_coef = volume_amp / t1;
	dfinish_coef = volume_amp / t2;

	int Max1, Max2;
	int number_peaks, max_frame_len;

	change_amplitude(dip1.buffer, dip1.dw_diplen, dstart_coef);
	change_amplitude(dip2.buffer, dip2.dw_diplen, dfinish_coef);

	Max1 = get_max_to(dip1.pitch_marks, dip1.num_pitch_marks);
	Max2 = get_max_to(dip2.pitch_marks, dip2.num_pitch_marks);
	max_frame_len = ((Max1 > Max2 ? Max1 : Max2) * 2 + 1) * 2;

	dip1.num_pitch_marks--; dip2.num_pitch_marks--;
	number_peaks = dip1.num_pitch_marks + dip2.num_pitch_marks;
	number_peaks--;
	bool new_window = false;
	int next_peak_index, number_of_window, win_counter, next_peak_index_old;
	win_counter = -1;
	double coef_mapping;

	for(int i = 0; i < number_frames; i++){
		double temp;
		temp = (double)(i) / (number_frames - 1) * (number_peaks - 1);
		nearest_peak_index = (int)(temp);
		if(temp >= nearest_peak_index + 0.5) nearest_peak_index++;

		if(new_window == false && i < number_frames){
			int k = i + 1;
			while(true){
				temp = (double)(k) / (number_frames - 1) * (number_peaks - 1);
				next_peak_index = (int)(temp);
				if(temp >= next_peak_index + 0.5) next_peak_index++;
			}

			if(next_peak_index >= nearest_peak_index + 1){
				if(k >= i + 2){
					number_of_window = k - i;
					coef_mapping = 1.0 / (number_of_window);
					new_window = true;
					win_counter = 0;
					next_peak_index_old = next_peak_index;
				}
			}
			k++;
		}

		delete[] cFrame;
		cFrame = new char[max_frame_len];
		memset(cFrame, 0, max_frame_len);

		if(nearest_peak_index < dip1.num_pitch_marks){
			tempt = dip1.pitch_marks[nearest_peak_index + 1] - dip1.pitch_marks[nearest_peak_index];
			frame_len = (tempt * 2 + 1) * 2;
			if(tempt < dip1.pitch_marks[nearest_peak_index]){
				memcpy(cFrame + (max_frame_len - frame_len) / 2,
					dip1.buffer + dip1.pitch_marks[nearest_peak_index] * 2 - tempt * 2, frame_len);
			}
			else{
				memcpy(cFrame + (max_frame_len - frame_len) / 2 + (tempt - dip1.pitch_marks[nearest_peak_index]) * 2,
					dip1.buffer, dip1.pitch_marks[nearest_peak_index] * 2);
				memcpy(cFrame + (max_frame_len - frame_len) / 2 + tempt * 2,
					dip1.buffer + dip1.pitch_marks[nearest_peak_index] * 2, tempt * 2);
			}
		}
		else{
			nearest_peak_index = nearest_peak_index - dip1.num_pitch_marks + 1;
			tempt = dip2.pitch_marks[nearest_peak_index + 1] - dip2.pitch_marks[nearest_peak_index];
			frame_len = (tempt * 2 + 1) * 2;
			if(tempt < dip2.pitch_marks[nearest_peak_index]){
				memcpy(cFrame + (max_frame_len - frame_len) / 2,
					dip2.buffer + dip2.pitch_marks[nearest_peak_index] * 2 - tempt * 2, frame_len);
			}
			else{
				memcpy(cFrame + (max_frame_len - frame_len) / 2 + (tempt - dip2.pitch_marks[nearest_peak_index]) * 2,
					dip2.buffer, dip2.pitch_marks[nearest_peak_index] * 2);
				memcpy(cFrame + (max_frame_len - frame_len) / 2 + tempt * 2,
					dip2.buffer + dip2.pitch_marks[nearest_peak_index] * 2, tempt * 2);
			}
		}

		hanning_window(cFrame + (max_frame_len - frame_len) / 2, frame_len);

		if(new_window && win_counter > 0){
			delete[] cFrame2;
			cFrame2 = new char[max_frame_len];
			memset(cFrame2, 0, max_frame_len);
			next_peak_index = next_peak_index_old;
			if(next_peak_index < dip1.num_pitch_marks){
				memcpy(cFrame + (max_frame_len - frame_len) / 2,
					dip1.buffer + dip1.pitch_marks[next_peak_index] * 2 - tempt * 2, frame_len);;
			}
			else{
				if(next_peak_index > dip1.num_pitch_marks){
					next_peak_index = next_peak_index - dip1.num_pitch_marks + 1;
					tempt = dip2.pitch_marks[nearest_peak_index + 1] - dip2.pitch_marks[nearest_peak_index];
					frame_len = (tempt * 2 + 1) * 2;
				}
				else next_peak_index = 1;

				if(tempt < dip2.pitch_marks[next_peak_index]){
					if((dip2.pitch_marks[nearest_peak_index] * 2 + frame_len / 2) < dip2.dw_diplen){
						memcpy(cFrame2 + (max_frame_len - frame_len) / 2,
							dip2.buffer + dip2.pitch_marks[next_peak_index] * 2 - tempt * 2, frame_len);
					}
					else{
						memcpy(cFrame2 + (max_frame_len - frame_len) / 2,
							dip2.buffer + dip2.pitch_marks[next_peak_index] * 2 - tempt * 2,
							dip2.dw_diplen - dip2.pitch_marks[next_peak_index] * 2 + tempt);
					}
				}
				else{
					memcpy(cFrame2 + (max_frame_len - frame_len) * 2 + (tempt - dip2.pitch_marks[next_peak_index]) * 2,
						dip2.buffer, dip2.pitch_marks[next_peak_index] * 2);
					memcpy(cFrame2 + (max_frame_len - frame_len) * 2 + tempt * 2,
						dip2.buffer + dip2.pitch_marks[next_peak_index] * 2, tempt * 2);
				}
			}

			hanning_window(cFrame + (max_frame_len - frame_len) * 2, frame_len);
			for(int j = 0; j < max_frame_len; j += 2){
				*(short *)(cFrame + j) = (short)((*(short *)(cFrame + j)) * (1.0 - coef_mapping * win_counter) + (*(short *)(cFrame2 + j)) * coef_mapping * win_counter);
			}

		}
		if(new_window) win_counter++;

		for(int j = 0; j < max_frame_len; j++){
			*(short *)(P.buffer + frame_position[i] + j - (max_frame_len - 2) / 2) += *(short *)(cFrame + j);
		}

		if(new_window && win_counter == number_of_window){
			new_window = false;
			win_counter = 0;
		}

		memcpy(P.buffer, dip1.buffer, dip1.pitch_marks[0] * 2);
		memcpy(P.buffer + frame_position[number_frames - 1], dip2.buffer + dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2,
				dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
		P.phone_len = frame_position[number_frames - 1] + dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2;
	}
	return true;
}
