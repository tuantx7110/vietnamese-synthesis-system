#include "diphone_synthesis.h"

int psola::sans_accent_from_phone(frame_position &st_frame_position, int new_to){
	float fnumber_position = float(st_frame_position.signal_len + st_frame_position.addition) / (new_to * 2);
	int number_position = rounding(fnumber_position);

	st_frame_position.position[0] = st_frame_position.start_point;
	if(number_position == 0){
		st_frame_position.position[1] = st_frame_position.start_point + new_to * 2;
		st_frame_position.number_position = 1;
		return st_frame_position.position[st_frame_position.number_position];
	}
	int i = 0;
	for(i = 0; i < number_position; i++){
		st_frame_position.position[i] = st_frame_position.start_point + i * new_to * 2;
	}
	st_frame_position.number_position = number_position;
	return st_frame_position.start_point + i * new_to * 2;
}

int psola::accent_grave_from_phone(frame_position &st_frame_position, int start_to, int finish_to){
	if(start_to == finish_to) return sans_accent_from_phone(st_frame_position, start_to);
	if((st_frame_position.signal_len + st_frame_position.addition) / (finish_to * 2) > st_frame_position.count){
		cout << "null pointer" << endl;
		return -1;
	}

	st_frame_position.position[0] = st_frame_position.start_point;
	if((st_frame_position.signal_len + st_frame_position.addition) / (finish_to * 2) == 0){
		st_frame_position.position[1] = st_frame_position.start_point + finish_to * 2;
		st_frame_position.number_position = 1;
		return st_frame_position.position[st_frame_position.number_position];
	}

	int i = st_frame_position.start_point;
	st_frame_position.position[0] = i;
	int j = 1;
	int additive_begin = start_to * 2;
	int additive = additive_begin;

	float half_step_to, fstep;
	int step;

	half_step_to = (float)(finish_to - start_to) * (finish_to + start_to) / (2 * ((st_frame_position.signal_len + st_frame_position.addition) - (finish_to - start_to))) * 2;
	st_frame_position.number_position = 0;

	while(i + additive < st_frame_position.signal_len + st_frame_position.addition + st_frame_position.start_point + finish_to * 2){
		i += additive;
		st_frame_position.position[j] = i;
		j++;
		st_frame_position.number_position++;

		fstep = j * half_step_to;
		step = rounding(fstep);

		additive = additive_begin + step * 2;
	}

	st_frame_position.number_position--;
	return st_frame_position.position[st_frame_position.number_position];
}

int psola::accent_aigu_from_phone(frame_position &st_frame_position, int start_to, int finish_to){
	if(start_to == finish_to) return sans_accent_from_phone(st_frame_position, start_to);

	if((st_frame_position.signal_len + st_frame_position.addition) / (finish_to * 2) > st_frame_position.count){
		cout << "null pointer" << endl;
		return -1;
	}

	st_frame_position.position[0] = st_frame_position.start_point;
	if((st_frame_position.signal_len + st_frame_position.addition) / (start_to * 2) == 0){
		st_frame_position.position[1] = st_frame_position.start_point + start_to * 2;
		st_frame_position.number_position = 1;
		return st_frame_position.position[st_frame_position.number_position];
	}

	int i = st_frame_position.start_point;
	st_frame_position.position[0] = i;
	int j = 1;
	int additive_begin = start_to * 2;
	int additive = additive_begin;

	float half_step_to, fstep;
	int step;

	half_step_to = (float)(start_to - finish_to) * (finish_to + start_to) / (2 * ((st_frame_position.signal_len + st_frame_position.addition) - (start_to - finish_to))) * 2;
	st_frame_position.number_position = 0;

	while(i + additive < st_frame_position.signal_len + st_frame_position.addition + st_frame_position.start_point + start_to * 2){
		i += additive;
		st_frame_position.position[j] = i;
		j++;
		st_frame_position.number_position++;

		fstep = j * half_step_to;
		step = rounding(fstep);

		additive = additive_begin - step * 2;
		if(additive < 0) break;
	}

	st_frame_position.number_position--;
	return st_frame_position.position[st_frame_position.number_position];
}


bool psola::create_phone(diphone dip1, diphone dip2, phone &P, int * frame_position, int number_frames){
	int nearest_peak_index;
	int frame_len;
	int tempt;
	char *cFrame;
	char *cFrame2;

	double t1, t2;
	int smax_p1, smax_p2, smax_n1, smax_n2;
	double dstart_coef, dfinish_coef;

	bool type_cn_flag = true;
	if(dip1.num_pitch_marks == 0) type_cn_flag = false;

	if(type_cn_flag){
		get_max_positive_value(dip1.buffer + dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, dip1.dw_diplen - dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, smax_p1);
		get_max_negative_value(dip1.buffer + dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, dip1.dw_diplen - dip1.pitch_marks[dip1.num_pitch_marks - 2] * 2, smax_n1);
		get_max_positive_value(dip2.buffer, dip2.pitch_marks[1] * 2, smax_p2);
		get_max_negative_value(dip2.buffer, dip2.pitch_marks[1] * 2, smax_n2);

		t1 = (smax_p1 - smax_n1) / 2.0;
		t2 = (smax_p2 - smax_n2) / 2.0;
		dstart_coef = volume_amp / t1;
		dfinish_coef = volume_amp / t2;
	}

	else{
		dstart_coef = get_max_abs_value((short *)dip1.buffer, dip1.dw_diplen / 2);
		dfinish_coef = get_max_abs_value((short *)dip2.buffer, dip2.dw_diplen / 2);
		dstart_coef = volume_amp / dstart_coef;
		dfinish_coef = volume_amp / dfinish_coef;
	}
	int Max1 = 0, Max2 = 0;
	int number_peaks, max_frame_len;

	if(type_cn_flag){

		change_amplitude(dip1.buffer, dip1.dw_diplen, dstart_coef);
		change_amplitude(dip2.buffer, dip2.dw_diplen, dfinish_coef);

		Max1 = get_max_to(dip1.pitch_marks, dip1.num_pitch_marks);
		Max2 = get_max_to(dip2.pitch_marks, dip2.num_pitch_marks);
		max_frame_len = ((Max1 > Max2 ? Max1 : Max2) * 2 + 1) * 2;
		cFrame = new char[max_frame_len];
		cFrame2 = new char[max_frame_len];
		cout << max_frame_len << " " << Max1 << " " << Max2 << endl;
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
					if(next_peak_index >= nearest_peak_index + 1){
						if(k >= i + 2){
							number_of_window = k - i;
							coef_mapping = 1.0 / (number_of_window);
							new_window = true;
							win_counter = 0;
							next_peak_index_old = next_peak_index;
						}
						break;
					}
					k++;
				}

			}

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

				memset(cFrame2, 0, max_frame_len);
				next_peak_index = next_peak_index_old;
				if(next_peak_index < dip1.num_pitch_marks){
					memcpy(cFrame2 + (max_frame_len - frame_len) / 2,
						dip1.buffer + dip1.pitch_marks[next_peak_index] * 2 - tempt * 2, frame_len);;
				}
				else{
					if(next_peak_index > dip1.num_pitch_marks){
						next_peak_index = next_peak_index - dip1.num_pitch_marks + 1;
						tempt = dip2.pitch_marks[nearest_peak_index + 1] - dip2.pitch_marks[nearest_peak_index];
						frame_len = (tempt * 2 + 1) * 2;
					}
					else next_peak_index = next_peak_index - dip1.num_pitch_marks + 1;

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
						memcpy(cFrame2 + (max_frame_len - frame_len) / 2 + (tempt - dip2.pitch_marks[next_peak_index]) * 2,
							dip2.buffer, dip2.pitch_marks[next_peak_index] * 2);
						memcpy(cFrame2 + (max_frame_len - frame_len) / 2 + tempt * 2,
							dip2.buffer + dip2.pitch_marks[next_peak_index] * 2, tempt * 2);
					}
				}

				hanning_window(cFrame2 + (max_frame_len - frame_len) / 2, frame_len);
				for(int j = 0; j < max_frame_len; j += 2){
					*(short *)(cFrame + j) = (short)((*(short *)(cFrame + j)) * (1.0 - coef_mapping * win_counter) + (*(short *)(cFrame2 + j)) * coef_mapping * win_counter);
				}

			}
			if(new_window) win_counter++;

			for(int j = 0; j < max_frame_len; j += 2){
				*(short *)(P.buffer + frame_position[i] + j - (max_frame_len - 2) / 2) += *(short *)(cFrame + j);
			}

			if(new_window && win_counter == number_of_window){
				new_window = false;
				win_counter = 0;
			}
		}

		memcpy(P.buffer, dip1.buffer, dip1.pitch_marks[0] * 2);
		memcpy(P.buffer + frame_position[number_frames - 1], dip2.buffer + dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2,
				dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
		P.phone_len = frame_position[number_frames - 1] + dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2;

	}
	else{
		double dcommon_coef = min(dstart_coef, dfinish_coef);
		change_amplitude(dip1.buffer, dip1.dw_diplen, dcommon_coef);
		change_amplitude(dip2.buffer, dip2.dw_diplen, dcommon_coef);

		Max2 = get_max_to(dip2.pitch_marks, dip2.num_pitch_marks);
		max_frame_len = (Max2 * 2 + 1) * 2;
		dip2.num_pitch_marks--;

		number_peaks = dip2.num_pitch_marks;
		bool new_window;
		int next_peak_index, number_of_window, win_counter, next_peak_index_old;
		float coef_mapping;
		new_window = false;
		win_counter = -1;
		cFrame = new char[max_frame_len];
		cFrame2 = new char[max_frame_len];
		for(int i = 0; i < number_frames; i++){
			float fnearest_peak_index;
			fnearest_peak_index = (float)(i) / (number_frames - 1) * (number_peaks - 1);
			nearest_peak_index = rounding(fnearest_peak_index);

			if(new_window == false && i < number_frames){
				int k = i + 1;
				while(true){
					fnearest_peak_index = (float)(k) / (number_frames - 1) * (number_peaks - 1);
					next_peak_index = rounding(fnearest_peak_index);
					if(next_peak_index >= nearest_peak_index + 1){
						if(k >= i + 2){
							number_of_window = k - i;
							coef_mapping = 1.0 / number_of_window;
							new_window = true;
							win_counter = 0;
							next_peak_index_old = next_peak_index;
						}
						break;
					}
					k++;
				}
			}

			//delete[] cFrame;
			//cFrame = new char[max_frame_len];
			memset(cFrame, 0, max_frame_len);

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

			hanning_window(cFrame + (max_frame_len - frame_len) / 2, frame_len);
			if(new_window && win_counter > 0){
				memset(cFrame2, 0, max_frame_len);
				next_peak_index = next_peak_index_old;

				memcpy(cFrame2 + (max_frame_len - frame_len) / 2,
					dip2.buffer + dip2.pitch_marks[next_peak_index] * 2 - tempt * 2, frame_len);
				hanning_window(cFrame2 + (max_frame_len - frame_len) / 2, frame_len);
				for(int j = 0; j < max_frame_len; j += 2){
					*(short *)(cFrame + j) = (short)((*(short *)(cFrame + j)) * (1.0 - coef_mapping * win_counter) + (*(short *)(cFrame2 + j) * coef_mapping * win_counter));
				}
				win_counter++;
			}
			if(new_window && win_counter == 0) win_counter++;

			for(int j = 0; j < max_frame_len; j += 2){
				*(short *)(P.buffer + frame_position[i] + j - (max_frame_len - 2) / 2) = *(short *)(cFrame + j);
			}

			if(new_window && win_counter == number_of_window){
				new_window = false;
				win_counter = 0;
			}
		}

		memcpy(P.buffer, dip1.buffer, dip1.dw_diplen);
		memcpy(P.buffer + dip1.dw_diplen, dip2.buffer, dip2.pitch_marks[0] * 2);
		memcpy(P.buffer + frame_position[number_frames - 1], dip2.buffer + dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2,
				dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
		P.phone_len = frame_position[number_frames - 1] + dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2;
	}
	delete[] cFrame2;
	delete[] cFrame;
	return true;
}

bool psola::accent_from_phone(diphone dip1, diphone dip2, phone &P, int *f0, int number_f0, int tone_type){
	int *to;
	int *segment_len;
	int number_to;
	frame_position st_frame_position;
	int end_point;
	int *len;

	bool type_cn_flag = true;
	bool f0_zero_flag = false;

	if(dip1.num_pitch_marks == 0) type_cn_flag = false;

	if(true){
		number_f0 = tone_for_syllable(tone_type, fo_begin, &f0, &len, P.new_handle_len, P.f_transition_point);
		if(number_f0 == -1) number_f0 = 0;
	}

	if(!number_f0){
		if(type_cn_flag){
			int average1 = get_average_to(dip1.pitch_marks, dip1.num_pitch_marks);
			int average2 = get_average_to(dip2.pitch_marks, dip2.num_pitch_marks);

			to = new int[2];
			to[0] = (average1 + average2) / 2;
			number_to = 1;
			segment_len = new int[2];
		}

		else{
			int average2 = get_average_to(dip2.pitch_marks, dip2.num_pitch_marks);
			to = new int[2];
			to[0] = average2;
			number_to = 1;
			segment_len = new int[2];
			f0_zero_flag = true;
		}
	}
	else{
		number_to = number_f0;
		to = new int[number_to];
		for(int i = 0; i < number_to; i++)
			to[i] = Sample_rate / f0[i];
	}

	int number_peak = dip2.num_pitch_marks;
	if(type_cn_flag) number_peak += dip1.num_pitch_marks;

	if(number_to == 1){

		st_frame_position.start_point = P.handle_point;
		st_frame_position.signal_len = P.new_handle_len;
		st_frame_position.count = P.new_handle_len / (to[0] * 2) + 20;
		st_frame_position.position = new int[st_frame_position.count];
		st_frame_position.addition = 0;

		if((!type_cn_flag) && f0_zero_flag){
			st_frame_position.number_position = dip2.num_pitch_marks;
			for(int i = 0; i < st_frame_position.number_position; i++){
				st_frame_position.position[i] = dip1.dw_diplen + dip2.pitch_marks[i] * 2;
			}
		}
		else{
			end_point = sans_accent_from_phone(st_frame_position, to[0]);
			if(end_point == 1){
				delete[] st_frame_position.position;
				delete[] to;
				return false;
			}

			st_frame_position.number_position++;
			st_frame_position.position[st_frame_position.number_position - 1] = end_point;
		}

		if(!create_phone(dip1, dip2, P, st_frame_position.position, st_frame_position.number_position)){
			delete[] st_frame_position.position;
			delete[] to;
			cout << "Error create new phone" << endl;
			return false;
		}
		delete[] st_frame_position.position;
		delete[] to;
		return true;
	}

	int position = P.handle_point;
	float f_signal_len = (float)(P.new_handle_len) / (number_to - 1);
	st_frame_position.signal_len = (int)(f_signal_len);
	if(f_signal_len >= (int)(f_signal_len) + 0.5)  st_frame_position.signal_len++;
	int temp = get_min_value(to, number_to);
	if(temp == 1){
		delete[] to;
		return false;
	}

	temp *= 2;
	st_frame_position.count = P.new_handle_len / temp + 10;
	st_frame_position.number_position = 0;
	int *p_position = new int[st_frame_position.count];
	st_frame_position.position = p_position;
	st_frame_position.start_point = P.handle_point;
	int number_position = 0;
	st_frame_position.addition = 0;

	for(int j = 0; j < number_to - 1; j++){
		if(true && (tone_type > 0 && tone_type <= 8)){
			st_frame_position.signal_len = len[j];
		}
		position = (to[j] < to[j + 1]) ? accent_grave_from_phone(st_frame_position, to[j], to[j + 1])
										:accent_aigu_from_phone(st_frame_position, to[j], to[j + 1]);
		st_frame_position.addition = st_frame_position.start_point + st_frame_position.addition + st_frame_position.signal_len - position;
		st_frame_position.start_point = position;
		st_frame_position.position = st_frame_position.position + st_frame_position.number_position;
		st_frame_position.count -= st_frame_position.number_position;
		number_position += st_frame_position.number_position;
	}

	st_frame_position.position = p_position;
	st_frame_position.number_position = number_position;
	st_frame_position.number_position++;
	st_frame_position.position[st_frame_position.number_position - 1] = position;

	if(!create_phone(dip1, dip2, P, st_frame_position.position, st_frame_position.number_position)){

		delete[] to;
		delete[] p_position;
		cout << "Error create new phone sau" << endl;
		return false;
	}
	if(true && (tone_type > 0 && tone_type <= 8)) delete[] len;
	delete[] p_position;
	delete[] to;
	return true;
}

WaveFile psola::create_syllable(syllable syl, diphone dip1, diphone dip2){
	bool type_cn_flag = true;
	if(dip1.num_pitch_marks == 0){
		type_cn_flag = false;
	}

	char *temp;
	phone P;
	int old_syllable_len = 0;

	if(type_cn_flag){
		P.handle_point = dip1.pitch_marks[0] * 2;
		if(dip1.tran_point > dip1.pitch_marks[0]){
			P.f_transition_point = (float)(dip1.tran_point * 2) / (dip1.dw_diplen + dip2.dw_diplen);
		}
		else P.f_transition_point = 0;

		P.new_handle_len = syl.syllable_len - dip1.pitch_marks[0] * 2 -
				(dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
		if(P.new_handle_len < 0){
			syl.syllable_len = dip1.dw_diplen + dip2.dw_diplen;
			P.new_handle_len = syl.syllable_len - dip1.pitch_marks[0] * 2 -
					(dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
			delete[] syl.new_syllable;
			syl.new_syllable = new char[syl.syllable_len];
		}

		if(syl.tone == 6){
			old_syllable_len = syl.syllable_len;
			syl.syllable_len += (int)(P.new_handle_len / 4.0) * 2;
			P.new_handle_len = (int)(3 * P.new_handle_len * 1.0 / 4) * 2;
		}
	}

	else{
		P.handle_point = dip1.dw_diplen + dip2.pitch_marks[0] * 2;
		if(dip2.tran_point > dip2.pitch_marks[0]){
			P.f_transition_point = (float)(dip1.dw_diplen + dip2.tran_point * 2)
					/(dip1.dw_diplen + dip2.dw_diplen);
		}
		else P.f_transition_point = 0;

		P.new_handle_len = syl.syllable_len - dip1.dw_diplen - dip2.pitch_marks[0] * 2 -
				(dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1] * 2);
		if(syl.tone == 6){
			old_syllable_len = syl.syllable_len;
			syl.syllable_len += (int)(P.new_handle_len / 4.0) * 2;
			P.new_handle_len = (int)(3 * P.new_handle_len * 1.0 / 4) * 2;
		}
		if(P.new_handle_len < 0){
			syl.syllable_len -= 2 * P.new_handle_len;
			P.new_handle_len = syl.syllable_len - dip1.dw_diplen - dip2.pitch_marks[0] * 2 -
					(dip2.dw_diplen - dip2.pitch_marks[dip2.num_pitch_marks - 1]);
			delete[] syl.new_syllable;
			syl.new_syllable = new char[syl.syllable_len];
		}
	}
	temp = (char *)calloc(syl.syllable_len + safe_buffer * 2, sizeof(char));
	memset(temp, 0, syl.syllable_len + safe_buffer * 2);
	P.buffer = temp + safe_buffer;
	P.buffer_max = syl.syllable_len;

	if(true){
		int new_number_f0;
		int *new_f0;
		int f0_begin;

		new_number_f0 = P.new_handle_len /2 /160;
		f0_begin = P.handle_point /2 /160;

		if((new_number_f0 + f0_begin)>syl.number_f0) new_number_f0 = syl.number_f0 - f0_begin;

		new_f0 = new int[new_number_f0];
		for(int i = 0; i < new_number_f0; i++){
			new_f0[i] = syl.f0[f0_begin + i];
		}

		delete [] syl.f0;
		syl.number_f0 = new_number_f0;
		syl.f0 = new int[new_number_f0];
		memcpy(syl.f0, new_f0, sizeof(int) * new_number_f0);
		delete [] new_f0;
	}

	if(!accent_from_phone(dip1, dip2, P,  syl.f0, syl.number_f0, syl.tone)){
		cout << "Ngu VKL" << endl;
	}

	free(temp);
	WaveFile W;
	W.init();
	vector<short> Vtemp;
	for(int i = 0; i < P.buffer_max; i += 2){
		Vtemp.push_back(*(short *)(P.buffer + i));
	}
	cout << "add_data ngon" << endl;
	W.add_data(Vtemp);
//	delete[] dip1.buffer;
//	delete[] dip2.buffer;
//	delete[] P.buffer;
//	delete[] syl.new_syllable;
	cout << "syllable ok" << endl;
	return W;
}

int psola::tone_for_syllable(int tone_type, int F0, int **f0, int **len, int len_of_syllable, float f_transition_point){
	if(tone_type < 1 || tone_type > 8) return -1;
	int num_of_control_point = 0;
	int counter = 0;
	int value_of_f0_1[4] =	{100,100,100, 90};
	int value_of_f0_2[4] =	{100, 95, 80, 75};
	int value_of_f0_3[8] = 	{100, 95, 85, 50, 50, 95, 120, 125};
	int value_of_f0_4[5] =	{100, 90, 75, 65, 90};
	int value_of_f0_5[4] =	{100, 100, 110, 125};
	int value_of_f0_6[5] =	{100, 95, 85, 55, 50};
	int value_of_f0_7[3] =	{100, 110, 125};
	int value_of_f0_8[3] =	{100, 88, 65};

	int control_position_1[3] = {33, 34, 33};
	int control_position_2[4] = {25, 25, 25, 25};
	int control_position_3[7] = {16, 17, 8, 18, 8, 17, 16};
	int control_position_6[4] = {25, 15, 15, 50};
	int control_position_7[2] = {40, 60};

	int l_transition_point = (int)(f_transition_point * len_of_syllable);
	len_of_syllable = len_of_syllable - l_transition_point;
	delete [] *f0;

	if(tone_type == 1){
		num_of_control_point = 5;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_1[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_1[counter - 1] / 100;
	}

	if(tone_type == 2){
		F0 = F0 * 92 / 100;
		num_of_control_point = 5;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_2[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_1[counter - 1] / 100;
	}

	if(tone_type == 3){
		F0 = F0 * 95 / 100;
		num_of_control_point = 9;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_3[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_3[counter - 1] / 100;
	}

	if(tone_type == 4){
		F0 = F0 * 92 / 100;
		num_of_control_point = 6;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_4[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_2[counter - 1] / 100;
	}

	if(tone_type == 5){
		F0 = F0 * 92 / 100;
		num_of_control_point = 5;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_5[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_1[counter - 1] / 100;
	}

	if(tone_type == 6){
		F0 = F0 * 90 / 100;
		num_of_control_point = 6;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_6[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_6[counter - 1] / 100;
	}

	if(tone_type == 7){
		num_of_control_point = 4;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_7[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_7[counter - 1] / 100;
	}

	if(tone_type == 8){
		num_of_control_point = 4;
		*f0 = new int[num_of_control_point];
		*len = new int[num_of_control_point - 1];
		for(counter = 1; counter < num_of_control_point; counter++)
			(*f0)[counter] = F0 * value_of_f0_8[counter - 1] / 100;
		for(counter = 1; counter < num_of_control_point - 1; counter++)
			(*len)[counter] = len_of_syllable * control_position_7[counter - 1] / 100;
	}

	(*f0)[0] = F0 * 98 / 100;
	(*len)[0] = l_transition_point;

	if((*len)[0] == 0){
		for(counter = 0; counter < num_of_control_point - 1; counter++)
			(*f0)[counter] = (*f0)[counter + 1];
		for(counter = 0; counter < num_of_control_point - 2; counter++)
			(*len)[counter] = (*len)[counter + 1];
		num_of_control_point--;
	}
	cout << "num_of_control_point " << num_of_control_point << endl;
	return num_of_control_point;
}


