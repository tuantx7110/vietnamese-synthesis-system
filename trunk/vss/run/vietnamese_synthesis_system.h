/*
 * vietnamese_synthesis_system.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <iostream>
#include <string>
using namespace std;

#include "../utils/string_utils.h"
#include "../utils/text_file_utils.h"
#include "../parser/tokenizer.h"
#include "../searcher/recorded_database_reader.h"

#define debug_vietnamese_synthesis_system 1

#ifndef VIETNAMESE_SYNTHESIS_SYSTEM_H_
#define VIETNAMESE_SYNTHESIS_SYSTEM_H_

class VietnameseSynthesisSystem {
public:
    VietnameseSynthesisSystem();
    virtual ~VietnameseSynthesisSystem();

    bool init();
    bool run(string input_text_file_name, string output_wave_file_name);

private:
    RecordedDatabaseReader recorded_database_reader;
    Tokenizer tokenizer;

    string raw_input_text;
    vector<string> tokens;
};

#endif /* VIETNAMESE_SYNTHESIS_SYSTEM_H_ */
