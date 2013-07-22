/*
 * main.cpp
 *
 *  Created on: May 21, 2013
 *      Author: quangpham
 */

#include <iostream>
#include <cstdio>
#include "../utils/constants.h"
#include "vietnamese_synthesis_system.h"
#include "../test/test_wave_file_utils.h"
#include "../test/test_binary_encoding.h"
#include "../searcher/binary_database_converter.h"
#include "../test/test_database_reader.h"
#include "../test/test_synthesis_diphone.h"
using namespace std;

void run_system() {
    VietnameseSynthesisSystem vss;

    if (!vss.init()) {
        cerr << "SYSTEM INITIATION FAILED!" << endl;
        return;
    }

    if (!vss.run(kInputTextFileName, kOutputWaveFileName)) {
        cerr << "SYSTEM RUNNING FAILED!" << endl;
        return;
    }

    cout << endl << "SPEECH SYNTHESIZED SUCCESSFULLY!" << endl;
}

void convert_database() {
	BinaryDatabaseConverter converter;
	converter.convert_to_binary();
}

int main() {
//	convert_database();
//	test_synthesis_diphone();
//	test_wave_file_utils();
    run_system();
    //  test_binary_encoding();
    //	test_binary_database_reader();
    return 0;
}
