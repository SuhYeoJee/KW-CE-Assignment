#include <systemc.h>

// Coefficients for each FIR
const sc_uint<8> coef[5] = { 18, 77, 107, 77, 18 };

SC_MODULE(fir) {
	sc_in< bool > clk;
	sc_in< bool > rst;

	sc_in< sc_int<16> > inp;
	sc_in< bool > inp_vld;
	sc_out< bool > inp_rdy;

	sc_out< sc_int<16> > outp;
	sc_out< bool > outp_vld;
	sc_in< bool > outp_rdy;

	SC_CTOR(fir) {
		SC_CTHREAD(fir_main, clk.pos());
		reset_signal_is(rst, true);
	}
	void fir_main() {
		// Reset code
		sc_int<16> taps[5] = { 0, 0, 0, 0, 0 };
		outp.write(0);
		wait();
		while (true) {
			for (int i = 4; i > 0; i--) {
				taps[i] = taps[i - 1];
			}
			taps[0] = inp.read();
			cout << "input:  "<<taps[0]<<endl;
			sc_int<16> val;
			for (int i = 0; i < 5; i++) {
				val += coef[i] * taps[i];
			}
			outp.write(val);
			wait();
		}
	}
};