#include "test_synthesis_diphone.h"

void test_synthesis_diphone(){
	synthesis Syn;
	Syn.init();
	WaveFile W = Syn.create_wave_file("hiếu");
	cout << "finish_move";
	write_wave_file(kOutputWaveFileName, W);
	cout << "finish";
}
