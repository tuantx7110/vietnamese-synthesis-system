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
    if (!input_text_reader.init()) {
        cerr << "Cannot initialize input text reader" << endl;
        return false;
    }
    if (!unit_searcher.init()) {
        cerr << "Cannot initialize unit searcher" << endl;
        return false;
    }
    return true;
}

bool VietnameseSynthesisSystem::run(string input_text_file_name, string output_wave_file_name) {
    if (!input_text_reader.read_input_text_file(input_text_file_name)) {
        cerr << "Cannot read input text file" << endl;
        return false;
    }

    unit_searcher.search(input_text_reader.get_all_sentences());

    return true;
}
