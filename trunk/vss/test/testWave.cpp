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

void testWave() {
	Wave wave;
	wave.readFromFile("/Users/quangpham/Desktop/test.wav");
	wave.writeToFile("/Users/quangpham/Desktop/result.wav");

	cout << wave.numberSamples << endl;
	cout << wave.sampleRate << endl;
	for (int i = 0; i < wave.numberSamples; ++i) {
		cout << wave.data[i] << " " << (i * 1000.0 / wave.sampleRate) << endl;
	}
}
