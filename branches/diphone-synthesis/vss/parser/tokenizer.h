#include "char_codec.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

class Tokenizer {
public:
    static const string kConfigurePath;
    static const string kDictionaryPath;

    Tokenizer();
    ~Tokenizer();

    string separator;
    vector<string> dicts;
    set<string> dic;
    char connection_symbol;
    CharCodec codec;

    bool load_configure();
    string trim(string str);
    vector<string> segment(string input_string);
};

#endif /* TOKENIZER_H_ */