/*
 * File:   constants.h
 * Author: quangpham
 *
 * Created on June 11, 2013, 9:15 AM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include <string>
#include "data_types.h"

using namespace std;

const int kBufferSize = 65536;
const int kLogWord = 6;
const int kWordSize = 1 << kLogWord;
const int kTotalBits = kWordSize * kBufferSize;
const word kFullBitMask = 0xFFFFFFFFFFFFFFFFLL;

const string kDataPath = "data/";
const string kInputTextFileName = kDataPath + "input_text.txt";
const string kOutputWaveFileName = kDataPath + "output_speech.wav";

const string kConfigurePath = "parser/configure/config.ini";
const string kDictionaryPath = "parser/dictionary/";

const string kRecordedDatabasePath = "searcher/recorded_database/";
const string kRecordedWavePath = kRecordedDatabasePath + "wave/";
const string kXmlRecordedDatabasePath = kRecordedDatabasePath + "recorded_database_description.xml";
const string kBinaryRecordedDatabasePath = kRecordedDatabasePath + "recorded_database_description.bin";
const string kDatabaseStatisticPath = kRecordedDatabasePath + "statistic.txt";

#endif	/* CONSTANTS_H */

