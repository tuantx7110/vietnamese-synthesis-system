/*
 * wave_file.h
 *
 *  Created on: May 31, 2013
 *      Author: quangpham
 */

#ifndef WAVE_FILE_H_
#define WAVE_FILE_H_

#include <vector>
#include <iostream>

using namespace std;

class WaveFile {
public:
    WaveFile();
    virtual ~WaveFile();

    void init();
    void update_size();
    void set_data(short data[], int n);
    void add_data(vector<short> more_data);
    void add_silence(int length);
    vector<short> get_data(int from, int to);
    vector<short> get_all_data();

    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short compression_code;
    short number_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
    vector<short> data;
};

#endif /* WAVE_FILE_H_ */
