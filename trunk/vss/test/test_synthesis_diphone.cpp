#include "test_synthesis_diphone.h"

void test_synthesis_diphone(){
	synthesis Syn;
	Syn.init();
	WaveFile W = Syn.create_wave_file("xoắn");
	write_wave_file(kOutputWaveFileName, W);
}
