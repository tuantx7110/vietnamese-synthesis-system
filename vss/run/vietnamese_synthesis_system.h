/*
 * vietnamese_synthesis_system.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <iostream>
#include <string>
using namespace std;

#include "../searcher/input_text_reader.h"
#include "../searcher/unit_searcher.h"

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
    InputTextReader input_text_reader;
    UnitSearcher unit_searcher;
};

#endif /* VIETNAMESE_SYNTHESIS_SYSTEM_H_ */
