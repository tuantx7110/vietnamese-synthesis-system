#include "syllable_synthesis.h"

void synthesis::init(){
	read_syllable_diphone();
	read_vowel_tone();
	read_diphone_binary();
}

void synthesis::read_syllable_diphone(){
	freopen("synthesis/diphone_data/all_syllables_diphone.in", "r", stdin);
	string s1, s2, s3;
	while(cin >> s1 >> s2 >> s3){
		syllable_map[s1] = syllable(s2, s3);
	}
}

void synthesis::read_vowel_tone(){
	freopen("synthesis/diphone_data/vowel_tone_ABC.dic", "r", stdin);
	char ch1[1005], ch2[1005];
	wchar_t wch1[1005], wch2[1005];
	int tone;
	CharCodec CC;
	while(scanf("%s %s %d", ch1, ch2, &tone) > 0){
		CC.UTF8Decode2BytesUnicode(wch1, ch1);
		CC.UTF8Decode2BytesUnicode(wch2, ch2);
		tone_map[wch1[0]] = make_pair(wch2[0], tone);
	}
}

//void read()

WaveFile synthesis::create_wave_file(string in){
	int tone = cut_tone(in);
	WaveFile W;
	W.init();
	if(syllable_map[in].left_diphone_name.length() != 0){
		cout << tone << " " << syllable_map[in].left_diphone_name << " " << syllable_map[in].right_diphone_name << endl;
		int pos1 = diphone_map[syllable_map[in].left_diphone_name], pos2 = diphone_map[syllable_map[in].right_diphone_name];
		add_data(W, pos1);
		add_data(W, pos2);
		return W;
	}
	else {
		cout << "đéo có";
		return W;
	}
}

void synthesis::add_data(WaveFile &W, int pos){
	FILE *f = fopen("synthesis/diphone_data/HALFSYL.DAT", "rb");
	char *header = new char[20000];
	char *temp = new char[20000];

	fseek(f, 0, SEEK_SET);
	fread(header, 1, 20000, f);
	fseek(f, (*(int *)(header + 8 * pos + 4 + 2)), SEEK_SET);
	fread(temp, 1, 20000, f);
	int diphone_len = *(int *)(temp + 3) - 8;
	cout << diphone_len << endl;
	vector<short> Vtemp;
	for(int i = 0; i < diphone_len; i += 2){
		Vtemp.push_back(*(short *)(temp + 28 + i));
	}
	W.add_data(Vtemp);
}

int synthesis::cut_tone(string &in){
	CharCodec CC;
	wchar_t wch[1005];
	char ch[1005];
	CC.UTF8Decode2BytesUnicode(wch, in.c_str());
	for(int i = 0; i < (int)wcslen(wch); i++){
		if(tone_map[wch[i]].second != 0){
			int ret = tone_map[wch[i]].second;
			wch[i] = tone_map[wch[i]].first;
			CC.UTF8Encode2BytesUnicode(ch, wch);
			in = ch;
			return ret;
		}
	}

	return 1;
}

void synthesis::read_diphone_binary(){
	FILE *f = fopen("synthesis/diphone_data/HALFSYL.DAT", "rb");

	short val = 0;
	fread(&val, 2, 1, f);
	cout << val << endl;

	for (int run = 0; run < val; ++run) {

		char name[5];
		fread(name, 1, 4, f);
		name[4] = '\0';
		diphone_map[(string)(name)] = run;
		int pos;
		fread(&pos, 4, 1, f);
	}

	char *header = new char[20000];
	char ch;

	fseek(f, 0, SEEK_SET);
	fread(header, 1, 20000, f);

	for(int run = 0; run < 1; run++){
		fseek(f, (*(int *)(header + 8 * run + 4 + 2)), SEEK_SET);
		for(int i = 0; i < 27; i++){
			fread(&ch, 1, 1, f);
		}
	}
	fclose(f);

}
