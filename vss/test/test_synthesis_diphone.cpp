#include "test_synthesis_diphone.h"

void test_synthesis_diphone() {
    /*
    synthesis Syn;
    Syn.init();
    WaveFile W = Syn.create_wave_file("quốc");
    cout << "finish_move";
    write_wave_file(kOutputWaveFileName, W);
    cout << "finish";
     */
    synthesis_many Syn;
    Syn.init();
    vector<WaveFile> W = Syn.create_wave_file("khắc");
    for (int i = 0; i < W.size(); i++) {
        write_wave_file(kDataPath + to_string(i, 2) + ".wav", W[i]);
    }
}
