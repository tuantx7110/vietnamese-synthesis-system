/*
 * text_file_utils.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#ifndef TEXT_FILE_UTILS_H_
#define TEXT_FILE_UTILS_H_

#include <string>
#include <fstream>
#include <iostream>
#include "string_utils.h"

using namespace std;

bool read_text_file(string file_name, string& raw_text);

#endif /* TEXT_FILE_UTILS_H_ */
