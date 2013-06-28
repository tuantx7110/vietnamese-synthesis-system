/*
 * testWave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include "test_wave_file_utils.h"

void test_wave_file_utils() {
    WaveFile wave_file;

    read_wave_file("/Users/quangpham/Desktop/test.wav", wave_file);
//    write_wave_file("/Users/quangpham/Desktop/result.wav", wave_file);

    cout << wave_file.chunk_id << endl;
    cout << wave_file.chunk_size << endl;
    cout << wave_file.format << endl;
    cout << wave_file.subchunk1_id << endl;
    cout << wave_file.subchunk1_size << endl;
    cout << wave_file.compression_code << endl;
    cout << wave_file.number_channels << endl;
    cout << wave_file.sample_rate << endl;
    cout << wave_file.byte_rate << endl;
    cout << wave_file.block_align << endl;
    cout << wave_file.bits_per_sample << endl;
    cout << wave_file.subchunk2_id << endl;
    cout << wave_file.subchunk2_size << endl;
}
