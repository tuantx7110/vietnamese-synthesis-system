/*
 * wave_file.cpp
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#include "wave_file.h"

WaveFile::WaveFile() {
    init();
}

WaveFile::~WaveFile() {
    // TODO Auto-generated destructor stub
}

void WaveFile::init() {
    chunk_id[0] = 'R';
    chunk_id[1] = 'I';
    chunk_id[2] = 'F';
    chunk_id[3] = 'F';
    chunk_size = 0;
    format[0] = 'W';
    format[1] = 'A';
    format[2] = 'V';
    format[3] = 'E';
    subchunk1_id[0] = 'f';
    subchunk1_id[1] = 'm';
    subchunk1_id[2] = 't';
    subchunk1_id[3] = ' ';
    subchunk1_size = 16;
    compression_code = 1;
    number_channels = 1;
    sample_rate = 16000;
    byte_rate = 32000;
    block_align = 2;
    bits_per_sample = 16;
    subchunk2_id[0] = 'd';
    subchunk2_id[1] = 'a';
    subchunk2_id[2] = 't';
    subchunk2_id[3] = 'a';
    subchunk2_size = 0;
    data.clear();
}

void WaveFile::update_size() {
    int bytes_per_sample = bits_per_sample / 8;
    int number_sample = data.size();
    subchunk2_size = number_sample * bytes_per_sample;
    chunk_size = subchunk2_size + 36;
}

void WaveFile::set_data(short data[], int n) {
    this->data.clear();
    for (int i = 0; i < n; ++i) {
        this->data.push_back(data[i]);
    }
}

void WaveFile::add_data(vector<short> more_data) {
    for (int i = 0; i < (int) more_data.size(); ++i) {
        data.push_back(more_data[i]);
    }
    update_size();
}

vector<short> WaveFile::get_data(int from, int to) {
    vector<short> result;
    for (int i = from; i <= to; ++i) {
        if (i >= (int) data.size()) {
            cerr << "Index out of data range" << endl;
            return result;
        }
        result.push_back(data[i]);
    }
    return result;
}

vector<short> WaveFile::get_all_data() {
	return data;
}
