/*
 * wave.h
 *
 *  Created on: May 16, 2013
 *      Author: quangpham
 */

#ifndef WAVE_H_
#define WAVE_H_

class Wave {
public:
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short audio_format;
    short number_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
    short bytes_per_sample;
    int number_samples;
    short *data;
    int read_wave_file(char *path);
    int write_wave_file(char *path);
};


#endif /* WAVE_H_ */
