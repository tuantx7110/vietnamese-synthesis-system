/*
 * text_file_utils.cpp
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include "text_file_utils.h"

bool read_text_file(string file_name, string &raw_text) {
    ifstream ifs(file_name.c_str());
    if (!ifs.is_open()) {
        cerr << "File " + file_name + " not found!" << endl;
        return false;
    }

    raw_text = "";
    string temp = "";

    while (getline(ifs, temp)) {
        trim_string(temp);
        raw_text = raw_text + " " + temp;
    }

    trim_string(raw_text);
    ifs.close();

    return true;
}

bool write_text_file(string file_name, string raw_text) {
    ofstream ofs(file_name.c_str());
    if (!ofs.is_open()) {
        cerr << "File " + file_name + " not found!" << endl;
        return false;
    }

    ofs << raw_text;
    ofs.close();

    return true;
}
