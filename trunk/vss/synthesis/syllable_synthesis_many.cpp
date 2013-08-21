/*
 * syllable_synthesis_many.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Administrator
 */

#include "syllable_synthesis_many.h"

void synthesis_many::init() {
    read_syllable_diphone();
    cout << "read_syllable_diphone done" << endl;
    read_diphone_binary();
    cout << "read_diphone_binary done" << endl;
}

void synthesis_many::read_syllable_diphone() {
    freopen(kDataDiphonePosition.c_str(), "r", stdin);
    string s1, s2, s3;
    int len, tone, energy, number_f0;
    int lef, rig;
    char temp[10005];
    while (gets(temp)) {
        istringstream iss(temp);
        iss >> s1 >> s2 >> s3 >> len >> tone >> energy >> number_f0;
        syllable_map[s1] = syllable(s2, s3, len, tone, energy, number_f0);
        syllable_map[s1].f0 = new int[number_f0];
        for (int i = 0; i < number_f0; i++) {
            iss >> syllable_map[s1].f0[i];
        }

        if (iss >> lef >> rig) {
            syllable_map[s1].left_diphone_position = lef;
            syllable_map[s1].right_diphone_position = rig;
        } else {
            syllable_map[s1].left_diphone_position = -1;
            syllable_map[s1].right_diphone_position = -1;
        }
    }
}

vector<WaveFile> synthesis_many::create_wave_file(string in) {
    syllable syl = syllable_map[in];
    cout << in << " " << syl.left_diphone_name << " " << syl.right_diphone_name << endl;
    vW.clear();
    vector<diphone> dip1 = get_diphone(syl.left_diphone_name);
    vector<diphone> dip2 = get_diphone(syl.right_diphone_name);
    psola ss;
    for (int i = 0; i < (int) dip1.size(); i++)
        for (int j = 0; j < (int) dip2.size(); j++) {
            cout << dip1[i].num_pitch_marks << " diphone " << dip2[j].num_pitch_marks << endl;
            WaveFile W = ss.create_syllable(syl, dip1[i], dip2[j]);
            cout << W.data.size() << endl;
            vW.push_back(W);
            cout << "memin" << endl;
        }

    cout << "ngon canh" << endl;
    return vW;

}

vector<diphone> synthesis_many::get_diphone(string in) {
    vector<int> poses = diphone_map[in];
    vector<diphone> vres;
    FILE *f = fopen("synthesis/diphone_data/HALFSYL.DAT", "rb");
    char *header = new char[40000];
    for (int i = 0; i < (int) poses.size(); i++) {
        char *temp = new char[40000];
        int pos = poses[i];
        diphone res;
        fseek(f, 0, SEEK_SET);
        fread(header, 1, 20000, f);
        fseek(f, (*(int *) (header + 8 * pos + 4 + 2)), SEEK_SET);
        fread(temp, 1, 20000, f);

        res.tran_point = (*(short *) (temp + 1));
        res.dw_diplen = (*(int *) (temp + 3)) - 8;
        res.buffer = new char[res.dw_diplen];
        memcpy(res.buffer, temp + 28, res.dw_diplen);

        int element_len = (*(int *) (header + 8 * (pos + 1) + 4 + 2)) - (*(int *) (header + 8 * pos + 4 + 2));
        res.num_pitch_marks = (element_len - 96 - 20 - (*(int *) (temp + 3))) / sizeof (int);
        res.pitch_marks = new int[res.num_pitch_marks];
        memcpy(res.pitch_marks, temp + 20 + (*(int *) (temp + 3)), res.num_pitch_marks * sizeof (int));
        vres.push_back(res);
        delete[] temp;
    }
    delete[] header;
    return vres;
}

void synthesis_many::read_diphone_binary() {
    FILE *f = fopen("synthesis/diphone_data/HALFSYL.DAT", "rb");

    short val = 0;
    fread(&val, 2, 1, f);
    cout << val << endl;

    for (int run = 0; run < val; ++run) {
        char name[5];
        fread(name, 1, 4, f);
        name[4] = '\0';
        diphone_map[(string) (name)].push_back(run);
        int pos;
        fread(&pos, 4, 1, f);
    }

    char *header = new char[20000];
    char ch;

    fseek(f, 0, SEEK_SET);
    fread(header, 1, 20000, f);

    for (int run = 0; run < 1; run++) {
        fseek(f, (*(int *) (header + 8 * run + 4 + 2)), SEEK_SET);
        for (int i = 0; i < 27; i++) {
            fread(&ch, 1, 1, f);
        }
    }
    fclose(f);

}
