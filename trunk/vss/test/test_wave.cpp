/*
 * testWave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include <cstdio>
#include "../utils/wave.h"

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

void test_wave() {
    Wave wave;
    wave.read_wave_file("/Users/quangpham/Desktop/test.wav");
    wave.write_wave_file("/Users/quangpham/Desktop/result.wav");

    cout << wave.number_samples << endl;
    cout << wave.sample_rate << endl;
    for (int i = 0; i < wave.number_samples; ++i) {
        cout << wave.data[i] << " " << (i * 1000.0 / wave.sample_rate) << endl;
    }
}
