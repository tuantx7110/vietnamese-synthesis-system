#include <iostream>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include "read_binary_file.h"
#include "../utils/wave_file.h"
#include "../utils/wave_file_utils.h"

using namespace std;

pair<int, int> P[2005];
char ch;
string diphone_name[2005];

string toString(int x){
	string s;
	x++;
	while(x){
		s.push_back(x % 10 + '0');
		x /= 10;
	}
	reverse(s.begin(), s.end());
	while(s.length() < 5) s = "0" + s;
	return s;
}

void read_file(string s){
	FILE *f = fopen(s.c_str(), "rb");

    short val = 0;

    fseek(f, 0, SEEK_END);
    int file_size = ftell(f);
    cout << file_size << endl;
    fseek(f, 0, SEEK_SET);
    fread(&val, 2, 1, f);
    cout << val << endl;

    for (int run = 0; run < val; ++run) {
		char name[5];
		fread(name, 1, 4, f);
		name[4] = '\0';
		diphone_name[run] = name;
		int pos;
		fread(&pos, 4, 1, f);
		P[run].first = pos;
		if(run) P[run - 1].second = pos;
    }
    P[val - 1].second = file_size;

    for(int i = val * 8 + 2; i <= 50000; i++) fread(&ch, 1, 1, f);

    for(int run = 0; run < val; run++){
    	vector<short> data;
    	short x;
    	for(int i = 0; i < 27; i++) {
    		fread(&ch, 1, 1, f);
    	}

    	for(int i = 0; i < (P[run].second - P[run].first - 27) / 2; i++){
    		fread(&x, 2, 1, f);
    		data.push_back(x);
    	}
    	fread(&ch, 1, 1, f);

//    	for(int i = 0; i < data.size(); i++) cout << data[i] << endl;
//    	cout << diphone_name[run] << endl;
    	WaveFile W;
    	W.add_data(data);
    	W.update_size();
    	write_wave_file( "diphone/data/" + toString(run) + diphone_name[run] + ".wav", W);
//    	cout << toString(run) << endl;
    }

}


