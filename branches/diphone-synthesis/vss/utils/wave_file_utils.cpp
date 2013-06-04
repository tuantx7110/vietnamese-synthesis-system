/*
 * wave.cpp
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#include "wave_file_utils.h"

bool read_wave_file(string path, WaveFile& wave_file) {
    FILE *file = fopen(path.c_str(), "rb");
    if (file == NULL) {
        cerr << "File " << path << " not found" << endl;
        return false;
    }

    // riff
    fread(wave_file.chunk_id, 1, 4, file);
    fread(&wave_file.chunk_size, 4, 1, file);
    fread(wave_file.format, 1, 4, file);

    // fmt
    fread(wave_file.subchunk1_id, 1, 4, file);
    fread(&wave_file.subchunk1_size, 4, 1, file);
    fread(&wave_file.compression_code, 2, 1, file);
    fread(&wave_file.number_channels, 2, 1, file);
    fread(&wave_file.sample_rate, 4, 1, file);
    fread(&wave_file.byte_rate, 4, 1, file);
    fread(&wave_file.block_align, 2, 1, file);
    fread(&wave_file.bits_per_sample, 2, 1, file);

    // data
    fread(wave_file.subchunk2_id, 1, 4, file);
    fread(&wave_file.subchunk2_size, 4, 1, file);

    int bytes_per_sample = wave_file.bits_per_sample / 8;
    int number_samples = wave_file.subchunk2_size / bytes_per_sample;
    short* data = new short[number_samples];
    fread(data, bytes_per_sample, number_samples, file);
    wave_file.set_data(data, number_samples);

    fclose(file);
    return true;
}

bool write_wave_file(string path, WaveFile wave_file) {
    FILE *file = fopen(path.c_str(), "wb");
    if (file == NULL) {
        cerr << "Path " << path << "not found" << endl;
        return false;
    }

    // riff
    fwrite(wave_file.chunk_id, 1, 4, file);
    fwrite(&wave_file.chunk_size, 4, 1, file);
    fwrite(wave_file.format, 1, 4, file);

    // fmt
    fwrite(wave_file.subchunk1_id, 1, 4, file);
    fwrite(&wave_file.subchunk1_size, 4, 1, file);
    fwrite(&wave_file.compression_code, 2, 1, file);
    fwrite(&wave_file.number_channels, 2, 1, file);
    fwrite(&wave_file.sample_rate, 4, 1, file);
    fwrite(&wave_file.byte_rate, 4, 1, file);
    fwrite(&wave_file.block_align, 2, 1, file);
    fwrite(&wave_file.bits_per_sample, 2, 1, file);

    // data
    fwrite(wave_file.subchunk2_id, 1, 4, file);
    fwrite(&wave_file.subchunk2_size, 4, 1, file);
    int bytes_per_sample = wave_file.bits_per_sample / 8;
    int number_samples = wave_file.subchunk2_size / bytes_per_sample;
    short* data = new short[number_samples];
    for (int i = 0; i < number_samples; ++i) {
        data[i] = wave_file.data[i];
    }
    fwrite(data, bytes_per_sample, number_samples, file);

    fclose(file);
    return true;
}
