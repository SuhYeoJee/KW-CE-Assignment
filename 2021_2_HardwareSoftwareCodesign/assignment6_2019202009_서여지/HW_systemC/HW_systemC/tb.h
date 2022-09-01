#include <systemc.h>

SC_MODULE(tb) {
	sc_in< bool > clk;
	sc_in< bool > rst;

	sc_out< sc_int<16> > inp;
	sc_out< bool > inp_vld;
	sc_in< bool > inp_rdy;

	sc_in< sc_int<16> > outp;
	sc_in< bool > outp_vld;
	sc_out< bool > outp_rdy;

	void source();
	void sink();

	SC_CTOR(tb) {
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};

void tb::source() {
	// Reset
	inp.write(0);
	rst.pos(); //rst.write(1);   // Assert reset (active high)
	wait();
	rst.neg(); //rst.write(0);   // De-assert reset
	wait();

	sc_int< 16 > tmp;
	// Send stimulus to FIR
	for (int i = 0; i < 64; i++) {
		if (i > 23 && i < 29)
			tmp = 256;
		else
			tmp = 0;
		if (i == 0) tmp = 1;

		inp.write(tmp);
		wait();
	}
}

void tb::sink() {
	sc_int< 16 > indata;
	// Read output coming from DUT
	for (int i = 0; i < 64; i++) {
		indata = outp.read();
		wait();
		cout << i << " :\t" << indata.to_int() << endl;
	}
	// End simulation
	sc_stop();
}