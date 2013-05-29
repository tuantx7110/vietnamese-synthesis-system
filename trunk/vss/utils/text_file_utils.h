/*
 * text_file_utils.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include "string_utils.h"

#ifndef TEXT_FILE_UTILS_H_
#define TEXT_FILE_UTILS_H_

bool read_text_file(string file_name, string& raw_text);


#endif /* TEXT_FILE_UTILS_H_ */
