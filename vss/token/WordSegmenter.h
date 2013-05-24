
#include "CharCoder.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class WordSegmenter{
public:
	string separator;
	vector<string> dicts;
	set<string> dic;
	string token_path;
	string data_path;
	char connectionSymbol;
	CharCoder CC;
	void loadConfigure(string dir);
	void splitSentence(string in, string out);
};
