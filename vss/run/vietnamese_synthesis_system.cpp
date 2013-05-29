/*
 * vietnamese_synthesis_system.cpp
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include "vietnamese_synthesis_system.h"

VietnameseSynthesisSystem::VietnameseSynthesisSystem() {
    // TODO
}

VietnameseSynthesisSystem::~VietnameseSynthesisSystem() {
    // TODO Auto-generated destructor stub
}

bool VietnameseSynthesisSystem::init() {
    if (!recorded_database_reader.load_data()) {
        cerr << "Cannot load recorded database description" << endl;
        return false;
    }

    if (!tokenizer.load_configure()) {
        cerr << "Cannot load tokenizer" << endl;
        return false;
    }

    raw_input_text = "";
    return true;
}

bool VietnameseSynthesisSystem::run(string input_text_file_name, string output_wave_file_name) {
    if (!read_text_file(input_text_file_name, raw_input_text)) {
        cerr << "Cannot read input text file" << endl;
        return false;
    }

    if (debug_vietnamese_synthesis_system) cout << "Raw input text = " + raw_input_text << endl;

    tokens = tokenizer.segment(raw_input_text);

    if (debug_vietnamese_synthesis_system) {
        cout << "Segmented text = ";
        for (int i = 0; i < (int) tokens.size(); ++i) {
            cout << tokens[i] << " ";
        }
        cout << endl;
    }

    return true;
}
