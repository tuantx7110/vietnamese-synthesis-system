/*
 * wave_file_utils.h
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */


#ifndef WAVE_FILE_UTILS_H_
#define WAVE_FILE_UTILS_H_

#include <string>
#include <cstdio>
#include <ctime>
#include "wave_file.h"

using namespace std;

bool read_wave_file(string path, WaveFile& wave_file);
bool read_wave_file(string path, int start, int finish, WaveFile& wave_file);
bool write_wave_file(string path, WaveFile wave_file);

#endif /* WAVE_FILE_UTILS_H_ */
