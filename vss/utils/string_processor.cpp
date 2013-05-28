#include <cctype>
#include <vector>
#include <sstream>
#include <iostream>
#include "string_processor.h"

string trim_string(string s) {
    while (s.length() > 0 && isspace(s[0])) s = s.substr(1);
    while (s.length() > 0 && isspace(s[s.length() - 1])) s = s.substr(0, s.length() - 1);
    return s;
}

vector<string> split_string(string s) {
    vector<string> res;

    istringstream iss(s);
    string temp;

    while (iss >> temp) {
        res.push_back(temp);
    }

    return res;
}

bool start_with_string(string s, string t) {
    if (s.length() < t.length()) {
        return false;
    }
    for (int i = 0; i < (int) t.length(); ++i) {
        if (s[i] != t[i]) {
            return false;
        }
    }
    return true;
}

bool parse_int(string s, int& ret) {
	s = trim_string(s);
	if (s.length() == 0) {
		cerr << "Parsing integer failed. Empty string.";
		return false;
	}

    ret = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        if (!isdigit(s[i])) {
            cerr << "Parsing integer failed. String " << s << " is not an integer.";
            return false;
        }
        ret = ret * 10 + s[i] - '0';
    }
    return true;
}

bool parse_double(string s, double& ret) {
	istringstream ss(s);
	ss >> ret;
	return true;
}

int first_index_of(string s, string t) {
    int s_length = (int) s.length();
    int t_length = (int) t.length();
    if (t_length == 0 || t_length > s_length) {
        return -1;
    }

    for (int i = 0; i + t_length - 1 < s_length; ++i) {
        if (s.substr(i, t_length) == t) {
            return i;
        }
    }
    return -1;
}

int last_index_of(string s, string t) {
    int s_length = (int) s.length();
    int t_length = (int) t.length();
    if (t_length == 0 || t_length > s_length) {
        return -1;
    }

    for (int i = s_length - t_length; i >= 0; --i) {
        if (s.substr(i, t_length) == t) {
            return i;
        }
    }
    return -1;
}
