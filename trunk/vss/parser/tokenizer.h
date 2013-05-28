#include "char_codec.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

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

    string trim(string str);
    void load_configure(string path);
    vector<string> segment(string input_string);
};
