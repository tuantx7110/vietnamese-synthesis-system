#include "syllable_synthesis.h"

void synthesis::init(){
	read_syllable_diphone();
	cout << "Read syllable diphone done!" << endl;
	read_diphone_binary();
	cout << "Read diphone binary done!" << endl;
}

void synthesis::read_syllable_diphone(){
	freopen(kDataDiphonePosition.c_str(), "r", stdin);
	string s1, s2, s3;
	int len, tone, energy, number_f0;
	int lef, rig;
	char temp[10005];
	while(gets(temp)){
		istringstream iss(temp);
		iss >> s1 >> s2 >> s3 >> len >> tone >> energy >> number_f0;
		syllable_map[s1] = syllable(s2, s3, len, tone, energy, number_f0);
		syllable_map[s1].f0 = new int[number_f0];
		for(int i = 0; i < number_f0; i++){
			iss >> syllable_map[s1].f0[i];
		}

		if(iss >> lef >> rig)
			if(iss >> lef >> rig){
				syllable_map[s1].left_diphone_position = lef;
				syllable_map[s1].right_diphone_position = rig;

			}
		else {
			syllable_map[s1].left_diphone_position = -1;
			syllable_map[s1].right_diphone_position = -1;
		}
	}
}

WaveFile synthesis::create_wave_file(string in){

	if(!syllable_map.count(in)){
		cout << "not find word " << in << " in database" << endl;
		WaveFile W;
		W.init();
		return W;
	}
	syllable syl = syllable(syllable_map[in].left_diphone_name, syllable_map[in].right_diphone_name,
			syllable_map[in].syllable_len, syllable_map[in].tone, syllable_map[in].energy, syllable_map[in].number_f0);
	syl.new_syllable = new char[syl.syllable_len];
	syl.f0 = new int[syl.number_f0];
	syl.left_diphone_position = syllable_map[in].left_diphone_position;
	syl.right_diphone_position = syllable_map[in].right_diphone_position;
	for(int i = 0; i < syl.number_f0; i++) syl.f0[i] = syllable_map[in].f0[i];
	cout << "Diphone [" << in << "] => [" << syl.left_diphone_name << "] + [" << syl.right_diphone_name << "] + " << " [tone = " << syl.tone << "]" << endl;
	diphone dip1, dip2;

	if(syl.left_diphone_position != -1){
		dip1 = get_diphone_position(syl.left_diphone_position);
		dip2 = get_diphone_position(syl.right_diphone_position);
	}
	else{
		if(!diphone_map.count(syl.left_diphone_name) || !diphone_map.count(syl.right_diphone_name)){
			cout << "Diphone not found in database" << endl;
			WaveFile W;
			W.init();
			return W;

		}
		dip1 = get_diphone(syl.left_diphone_name);
		dip2 = get_diphone(syl.right_diphone_name);
	}

	psola ss;
	WaveFile W = ss.create_syllable(syl, dip1, dip2);
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
	int element_len;
	if(pos == number_diphone - 1){
		fseek(f, 0L, SEEK_END);
		element_len = ftell(f) - (*(int *)(header + 8 * pos + 4 + 2));
	}
	else element_len = (*(int *)(header + 8 * (pos + 1) + 4 + 2)) - (*(int *)(header + 8 * pos + 4 + 2));

	res.num_pitch_marks = (element_len - 96 - 20 - (*(int *)(temp + 3))) / sizeof(int);
	res.pitch_marks = new int[res.num_pitch_marks];
	memcpy(res.pitch_marks,temp + 20 + (*(int *)(temp + 3)),res.num_pitch_marks * sizeof(int));
	delete[] header;
	delete[] temp;
	return res;
}

diphone synthesis::get_diphone(string in){
	int pos = diphone_map[in];
	cout << in << " " << pos << endl;
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

	fread(&number_diphone, 2, 1, f);

	for (int run = 0; run < number_diphone; ++run) {

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
