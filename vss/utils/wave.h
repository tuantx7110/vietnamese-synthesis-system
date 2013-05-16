/*
 * wave.h
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#ifndef WAVE_H_
#define WAVE_H_

#include <cstdio>

class Wave {
private:
	char chunkId[4];
	int chunkSize;
	char format[4];
	char subchunk1Id[4];
	int subchunk1Size;
	short audioFormat;
	short numberChannels;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
	char subchunk2Id[4];
	int subchunk2Size;
	short bytesPerSample;
	int numberSamples;
	short *data;
public:
	int readFromFile(char *path);
	int writeToFile(char *path);
};


#endif /* WAVE_H_ */
