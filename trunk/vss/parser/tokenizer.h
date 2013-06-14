
#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <vector>
#include <set>
#include "char_codec.h"
#include "../utils/constants.h"

using namespace std;

class Tokenizer {
public:
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
