#include <systemc.h>

SC_MODULE(Three_Processes) { // declare module class
	sc_in <bool> clk;
	SC_CTOR(Three_Processes) : sc_clock clk("clock", 10, SC_NS) {

		SC_THREAD(first_thread);// register the first thread process
		sensitive << clk.pos();
		SC_THREAD(second_thread);// register the second thread process
		sensitive << clk.pos();
		SC_THREAD(third_thread);// register the third thread process
		sensitive << clk.pos();
	}//end constructor

	void first_thread(void)
	void second_thread(void);
	void third_thread(void);
};