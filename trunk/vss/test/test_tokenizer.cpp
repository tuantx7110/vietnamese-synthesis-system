
#include "test_tokenizer.h"

void test_tokenizer() {
    ifstream ifs((kDataPath + "file1.vn").c_str());
    ofstream ofs((kDataPath + "file1.tok").c_str());

    Tokenizer tokenizer;

    string str;
    while (getline(ifs, str)) {
        vector<string> tokens = tokenizer.segment(str);
        for (int i = 0; i < (int)tokens.size(); ++i) {
            ofs << tokens[i] << " ";
        }
        ofs << endl;
    }
}
