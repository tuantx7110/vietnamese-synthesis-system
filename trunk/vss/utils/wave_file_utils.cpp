/*
 * wave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include <cstdio>
#include "wave_file_utils.h"

int Wave::read_wave_file(char *path) {
    FILE *file = fopen(path, "rb");

    // riff
    fread(chunk_id, 1, 4, file);
    fread(&chunk_size, 4, 1, file);
    fread(format, 1, 4, file);

    // fmt
    fread(&subchunk1_id, 1, 4, file);
    fread(&subchunk1_size, 4, 1, file);
    fread(&audio_format, 2, 1, file);
    fread(&number_channels, 2, 1, file);
    fread(&sample_rate, 4, 1, file);
    fread(&byte_rate, 4, 1, file);
    fread(&block_align, 2, 1, file);
    fread(&bits_per_sample, 2, 1, file);

    // data
    fread(&subchunk2_id, 1, 4, file);
    fread(&subchunk2_size, 4, 1, file);
    bytes_per_sample = bits_per_sample / 8;
    number_samples = subchunk2_size / bytes_per_sample;
    data = new short[number_samples];
    fread(data, bytes_per_sample, number_samples, file);

    fclose(file);
    return 0;
}

int Wave::write_wave_file(char *path) {
    FILE *file = fopen(path, "wb");

    // riff
    fwrite(chunk_id, 1, 4, file);
    fwrite(&chunk_size, 4, 1, file);
    fwrite(format, 1, 4, file);

    // fmt
    fwrite(&subchunk1_id, 1, 4, file);
    fwrite(&subchunk1_size, 4, 1, file);
    fwrite(&audio_format, 2, 1, file);
    fwrite(&number_channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    fwrite(&byte_rate, 4, 1, file);
    fwrite(&block_align, 2, 1, file);
    fwrite(&bits_per_sample, 2, 1, file);

    // data
    fwrite(&subchunk2_id, 1, 4, file);
    fwrite(&subchunk2_size, 4, 1, file);
    bytes_per_sample = bits_per_sample / 8;
    number_samples = subchunk2_size / bytes_per_sample;
    fwrite(data, bytes_per_sample, number_samples, file);

    fclose(file);
    return 0;
}
