/*
 * wave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include "wave.h"

int Wave::readFromFile(char *path) {
	FILE *file = fopen(path, "rb");

	// riff
	fread(chunkId, 1, 4, file);
	fread(&chunkSize, 4, 1, file);
	fread(format, 1, 4, file);

	// fmt
	fread(&subchunk1Id, 1, 4, file);
	fread(&subchunk1Size, 4, 1, file);
	fread(&audioFormat, 2, 1, file);
	fread(&numberChannels, 2, 1, file);
	fread(&sampleRate, 4, 1, file);
	fread(&byteRate, 4, 1, file);
	fread(&blockAlign, 2, 1, file);
	fread(&bitsPerSample, 2, 1, file);

	// data
	fread(&subchunk2Id, 1, 4, file);
	fread(&subchunk2Size, 4, 1, file);
	bytesPerSample = bitsPerSample / 8;
	numberSamples = subchunk2Size / bytesPerSample;
	data = new short[numberSamples];
	fread(data, bytesPerSample, numberSamples, file);

	fclose(file);
	return 0;
}

int Wave::writeToFile(char *path) {
	FILE *file = fopen(path, "wb");

	// riff
	fwrite(chunkId, 1, 4, file);
	fwrite(&chunkSize, 4, 1, file);
	fwrite(format, 1, 4, file);

	// fmt
	fwrite(&subchunk1Id, 1, 4, file);
	fwrite(&subchunk1Size, 4, 1, file);
	fwrite(&audioFormat, 2, 1, file);
	fwrite(&numberChannels, 2, 1, file);
	fwrite(&sampleRate, 4, 1, file);
	fwrite(&byteRate, 4, 1, file);
	fwrite(&blockAlign, 2, 1, file);
	fwrite(&bitsPerSample, 2, 1, file);

	// data
	fwrite(&subchunk2Id, 1, 4, file);
	fwrite(&subchunk2Size, 4, 1, file);
	bytesPerSample = bitsPerSample / 8;
	numberSamples = subchunk2Size / bytesPerSample;
	fwrite(data, bytesPerSample, numberSamples, file);

	fclose(file);
	return 0;
}
