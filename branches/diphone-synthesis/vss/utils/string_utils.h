/*
 * File:   string_utils.h
 * Author: quangpham
 *
 * Created on May 28, 2013, 11:57 AM
 */
#include <string>
#include <vector>
using namespace std;

#ifndef STRING_UTILS_H
#define	STRING_UTILS_H

void trim_string(string& s);
vector<string> split_string(string s);
bool start_with_string(string s, string t);
void replace_all(string& s, char from_char, char to_char);
bool parse_int(string s, int& ret);
bool parse_double(string s, double &ret);
int first_index_of(string s, string t);
int last_index_of(string s, string t);
bool is_punctuation(string s);
bool is_long_silence(string s);

#endif	/* STRING_UTILS_H */

