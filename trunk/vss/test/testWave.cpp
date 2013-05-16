/*
 * testWave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include <cstdio>
#include "../utils/wave.h"

int main() {
	Wave wave;
	wave.readFromFile("/Users/quangpham/Desktop/test.wav");
	wave.writeToFile("/Users/quangpham/Desktop/result.wav");
	return 0;
}
