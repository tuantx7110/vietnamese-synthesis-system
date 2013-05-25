
#include "CharCoder.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class WordSegmenter{
public:
	static const string token_path;
	static const string data_path;

	string separator;
	vector<string> dicts;
	set<string> dic;
	char connectionSymbol;
	CharCoder CC;

	void loadConfigure(string dir);
	void splitSentence(string in, string out);
};
