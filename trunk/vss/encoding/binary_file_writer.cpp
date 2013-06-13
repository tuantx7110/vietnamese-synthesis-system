/*
 * File:   binary_file_writer.cpp
 * Author: quangpham
 *
 * Created on June 10, 2013, 10:48 AM
 */

#include "binary_file_writer.h"

BinaryFileWriter::BinaryFileWriter() {
}

BinaryFileWriter::BinaryFileWriter(string file_name) {
    open(file_name);
}

BinaryFileWriter::~BinaryFileWriter() {
    close();
}

bool BinaryFileWriter::open(string file_name) {
    this->file_name = file_name;

    file = fopen(file_name.c_str(), "wb");
    if (file == NULL) {
        cerr << "Cannot open file " << file_name << " for writing" << endl;
        opened = false;
        return false;
    }

    memset(buffer, 0, sizeof (buffer));
    pointer = 0;
    opened = true;

    return true;
}

void BinaryFileWriter::close() {
    if (opened) {
        if (pointer > 0) {
            fwrite(buffer, sizeof (word), (pointer >> kLogWord) + 1, file);
        }
        fclose(file);
        opened = false;
    }
}

void BinaryFileWriter::flush_buffer() {
    int iword = get_iword();
    pointer = get_ibit();
    word temp = buffer[iword];
    fwrite(buffer, sizeof (word), iword, file);
    memset(buffer, 0, sizeof (buffer));
    buffer[0] = temp;
}

void BinaryFileWriter::write_bits(int bit, int length) {
    if (buffer_capacity() < length) flush_buffer();

    if (buffer_capacity() < length) {
        int part = length >> 1;
        write_bits(bit, part);
        write_bits(bit, length - part);
        return;
    }

    int iword = get_iword();
    int ibit = get_ibit();
    pointer += length;

    if (bit == 1) {
        if (ibit + length <= kWordSize) {
            buffer[iword] |= mask(length) << ibit;
        } else {
            buffer[iword] |= mask(kWordSize - ibit) << ibit;

            length -= (kWordSize - ibit);
            ++iword;

            while (length >= kWordSize) {
                buffer[iword] |= kFullBitMask;
                length -= kWordSize;
                ++iword;
            }

            if (length > 0) {
                buffer[iword] |= mask(length);
            }
        }
    }
}

bool BinaryFileWriter::write_unary(int number) {
    if (!opened) {
        error_file_not_opened();
        return false;
    }
    if (number <= 0) {
        cerr << "Unary coding only works for positive integer, cannot work for number = " << number << endl;
        return false;
    }
    write_bits(0, number - 1);
    write_bits(1);
    return true;
}

bool BinaryFileWriter::write_gamma(int number) {
    if (!opened) {
        error_file_not_opened();
        return false;
    }
    if (number <= 0) {
        cerr << "Gamma coding only works for positive integer, cannot work for number = " << number << endl;
        return false;
    }

    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    --n;

    write_bits(0, n);
    for (int i = n; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
    return true;
}

bool BinaryFileWriter::write_delta(int number) {
    if (!opened) {
        error_file_not_opened();
        return false;
    }
    if (number <= 0) {
        cerr << "Delta coding only works for positive integer, cannot work for number = " << number << endl;
        return false;
    }

    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    n--;

    write_gamma(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
    return true;
}

bool BinaryFileWriter::write_omega(int number) {
    if (!opened) {
        error_file_not_opened();
        return false;
    }
    if (number <= 0) {
        cerr << "Omega coding only works for positive integer, cannot work for number = " << number << endl;
        return false;
    }

    write_recursive_omega(number);
    write_bits(0);

    return true;
}

void BinaryFileWriter::write_recursive_omega(int number) {
    if (number == 1) return;

    int n = 0;
    for (int temp = number; temp > 0; temp >>= 1) ++n;
    write_recursive_omega(n - 1);

    for (int i = n - 1; i >= 0; --i) {
        write_bits(bit_at(number, i));
    }
}

void BinaryFileWriter::write_string(string s) {
    const int s_len = s.length();
    wchar_t w[s_len];
    codec.UTF8Decode2BytesUnicode(w, s.c_str());
    int w_len = wcslen(w);

    write_omega(s_len);
    write_omega(w_len);
    for (int i = 0; i < w_len; ++i) {
        write_omega((int) (w[i]));
    }
}
