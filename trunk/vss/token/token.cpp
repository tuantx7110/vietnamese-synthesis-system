
#include "WordSegmenter.h"
#include "token.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <sstream>

void Token::token(string in, string out){
	//string path = "vietnamese-synthesis-system\\vss\\data";
	WordSegmenter ws;
	ws.loadConfigure("config.ini");
	ws.splitSentence(in, out);
	cout << "mission complete";
}
