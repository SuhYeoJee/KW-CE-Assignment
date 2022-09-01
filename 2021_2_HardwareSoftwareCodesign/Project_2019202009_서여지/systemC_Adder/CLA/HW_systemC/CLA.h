#include <systemc.h>

SC_MODULE(cla32) {
	sc_in< bool > clk;

	sc_in< sc_int<32> > A;
	sc_in<sc_int<1> > A_valid;
	sc_out<sc_int<1> > A_ready;

	sc_in< sc_int<32> > B;
	sc_in<sc_int<1> > B_valid;
	sc_out<sc_int<1> > B_ready;

	sc_in< sc_int<1> > Cin;
	sc_in<sc_int<1> > Cin_valid;
	sc_out<sc_int<1> > Cin_ready;

	sc_out< sc_int<32> > result;
	sc_out<sc_int<1> > result_valid;
	sc_in<sc_int<1> > result_ready;

	sc_out< sc_int<1> > Cout;
	sc_out<sc_int<1> > Cout_valid;
	sc_in<sc_int<1> > Cout_ready;

	void cla32_main();

	SC_CTOR(cla32) {
		SC_CTHREAD(cla32_main, clk.pos());
	}
};