/*
 * wave_file_utils.h
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include <string>
#include <cstdio>

using namespace std;

#include "wave_file.h"

#ifndef WAVE_FILE_UTILS_H_
#define WAVE_FILE_UTILS_H_

bool read_wave_file(string path, WaveFile& wave_file);
bool write_wave_file(string path, WaveFile wave_file);

#endif /* WAVE_FILE_UTILS_H_ */
