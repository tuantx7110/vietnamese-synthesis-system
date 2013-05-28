#include "tokenizer.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

const string Tokenizer::kConfigurePath = "parser/configure/config.ini";
const string Tokenizer::kDictionaryPath = "parser/dictionary/";

Tokenizer::Tokenizer() {
    load_configure(kConfigurePath);
}

Tokenizer::~Tokenizer() {
}

vector<string> Tokenizer::segment(string input_string) {
    istringstream iss(input_string);
    vector<string> words;
    string str;

    while (iss >> str) {
        vector<string> split = codec.processString(str);
        for (int i = 0; i < (int) split.size(); i++) {
            words.push_back(split[i]);
        }
    }

    vector<string> res;
    int run = 0, size;

    while (run < (int) words.size()) {
        size = 1;
        for (int len = 4; len >= 2; len--) {
            if (run + len - 1 >= (int) words.size()) continue;
            str = "";
            for (int i = 1; i <= len; i++) {
                str += words[run + i - 1];
                if (i < len) str += " ";
            }
            if (dic.count(str)) {
                size = len;
                str = "";
                for (int i = 1; i <= len; i++) {
                    str += words[run + i - 1];
                    if (i < len) str += connection_symbol;
                }
                res.push_back(str);
                break;
            }
        }
        if (size == 1) {
            res.push_back(words[run]);
        }
        run += size;
    }

    return res;
}

string Tokenizer::trim(string str) {
    while (str[0] == '#' || str[0] == ' ' || str[0] == '\n' || str[0] == '\r') str = str.substr(1, str.length() - 1);
    while (str[str.length() - 1] == ' ' || str[str.length() - 1] == '\n' || str[str.length() - 1] == '\r' || str[str.length() - 1] == '#')
        str = str.substr(0, str.length() - 1);
    return str;
}

void Tokenizer::load_configure(string path) {
    ifstream ifs;
    ifs.open(path.c_str());

    string s;
    char buff[2000];
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            ifs >> s;
            if (s.length() > 12 && s.substr(0, 11).compare("<dictionary") == 0) {
                dicts.push_back(s.substr(15, s.length() - 15));
            }
            if (s.length() > 19 && s.substr(0, 19).compare("<seperate_character") == 0) {
                separator = s.substr(23, s.length() - 23);
            }
            if (s.length() > 13 && s.substr(0, 13).compare("<connect_char") == 0) {
                connection_symbol = s[15];
            }
        }
    } else {
        cerr << "loi file " << path << endl;
    }
    ifs.close();
    for (int i = 0; i < (int) dicts.size(); i++) {
        ifs.open((kDictionaryPath + dicts[i]).c_str());
        while (!ifs.eof()) {
            ifs.getline(buff, 1999);
            s = buff;
            dic.insert(trim(s));
        }
        cout << dicts[i] << " " << dic.size() << endl;
        ifs.close();
    }
    ifs.open((kDictionaryPath + separator).c_str());
    ifs.getline(buff, 1999);
    codec.readSeparator(buff);
    ifs.close();
}
