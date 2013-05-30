/*
 * input_text_reader.cpp
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include "input_text_reader.h"

InputTextReader::InputTextReader() {
    // TODO Auto-generated constructor stub

}

InputTextReader::~InputTextReader() {
    // TODO Auto-generated destructor stub
}

vector<SearchingSentence>& InputTextReader::get_all_searching_sentences() {
    return all_searching_sentences;
}

bool InputTextReader::init() {
	cout << "Initializing input text reader ..." << endl << endl;

    if (!tokenizer.load_configure()) {
        cerr << "Cannot load tokenizer" << endl;
        return false;
    }

    raw_input_text = "";
    tokens.clear();
    all_searching_sentences.clear();

    cout << "Input text reader initialized successfully" << endl << endl;
    return true;
}

bool InputTextReader::read_input_text_file(string file_name) {
    if (!read_text_file(file_name, raw_input_text)) {
        cerr << "Cannot read input text file" << endl;
        return false;
    }

    if (debug_input_text_reader) cout << "Raw input text = " + raw_input_text << endl;

    if (!parse_input_text()) {
        cerr << "Error parsing input text" << endl;
        return false;
    }

    return true;

}

bool InputTextReader::parse_input_text() {
    tokens = tokenizer.segment(raw_input_text);

    if (debug_input_text_reader) {
        cout << "Segmented text = ";
        for (int i = 0; i < (int) tokens.size(); ++i) {
            cout << tokens[i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < (int) tokens.size(); ++i) {
        replace_all(tokens[i], '_', ' ');
    }

    all_searching_sentences.clear();

    SearchingSentence searching_sentence;


    return true;
}
