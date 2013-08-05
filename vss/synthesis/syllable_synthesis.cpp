#include "syllable_synthesis.h"

void synthesis::init(){
	read_syllable_diphone();
	cout << "read_syllable_diphone done" << endl;
	read_diphone_binary();
	cout << "read_diphone_binary done" << endl;
}

void synthesis::read_syllable_diphone(){
	freopen(kDataDiphonePosition.c_str(), "r", stdin);
	string s1, s2, s3;
	int len, tone, energy, number_f0;
	int lef, rig;
	while(cin >> s1 >> s2 >> s3 >> len >> tone >> energy >> number_f0){

		syllable_map[s1] = syllable(s2, s3, len, tone, energy, number_f0);
		syllable_map[s1].f0 = new int[number_f0];
		for(int i = 0; i < number_f0; i++){
			cin >> syllable_map[s1].f0[i];
		}
		cin >> lef >> rig;
		syllable_map[s1].left_diphone_position = lef;
		syllable_map[s1].right_diphone_position = rig;
		cout << s1 << " " << s2 << " " << s3 << " " << lef << " " << rig << endl;

	}
}

WaveFile synthesis::create_wave_file(string in){

	if(!syllable_map.count(in)){
		WaveFile W;
		W.init();
		return W;
	}

	syllable syl = syllable_map[in];
	cout << in << " " << syl.left_diphone_name << " " << syl.right_diphone_name << " " << syl.left_diphone_position << " " << syl.right_diphone_position << endl;

	diphone dip1 = get_diphone_position(syl.left_diphone_position);
	diphone dip2 = get_diphone_position(syl.right_diphone_position);

	psola ss;
	WaveFile W = ss.create_syllable(syl, dip1, dip2);

	cout << "ngon canh" << endl;
	return W;

}

diphone synthesis::get_diphone_position(int pos){
	diphone res;
	FILE *f = fopen(kDataHalfsyl.c_str(), "rb");
	char *header = new char[20000];
	char *temp = new char[20000];

	fseek(f, 0, SEEK_SET);
	fread(header, 1, 20000, f);
	fseek(f, (*(int *)(header + 8 * pos + 4 + 2)), SEEK_SET);
	fread(temp, 1, 20000, f);

	res.tran_point = (*(short *)(temp + 1));
	res.dw_diplen = (*(int *)(temp + 3)) - 8;
	res.buffer = new char[res.dw_diplen];
	memcpy(res.buffer, temp + 28, res.dw_diplen);

	int element_len = (*(int *)(header + 8 * (pos + 1) + 4 + 2)) - (*(int *)(header + 8 * pos + 4 + 2));
	res.num_pitch_marks = (element_len - 96 - 20 - (*(int *)(temp + 3))) / sizeof(int);
	res.pitch_marks = new int[res.num_pitch_marks];
	memcpy(res.pitch_marks,temp + 20 + (*(int *)(temp + 3)),res.num_pitch_marks * sizeof(int));
	delete[] header;
	delete[] temp;
	return res;
}

diphone synthesis::get_diphone(string in){
	int pos = diphone_map[in];
	return get_diphone_position(pos);
}

void synthesis::add_data(WaveFile &W, int pos){
	FILE *f = fopen(kDataHalfsyl.c_str(), "rb");
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

void synthesis::read_diphone_binary(){
	FILE *f = fopen(kDataHalfsyl.c_str(), "rb");

	short val = 0;
	fread(&val, 2, 1, f);
	cout << val << endl;

	for (int run = 0; run < val; ++run) {

		char name[5];
		fread(name, 1, 4, f);
		name[4] = '\0';
		if(!diphone_map.count((string)(name)))
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
