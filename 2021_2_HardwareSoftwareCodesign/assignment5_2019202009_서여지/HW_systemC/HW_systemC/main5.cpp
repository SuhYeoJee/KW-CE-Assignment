#include <systemc.h>
#include "Three_Process.h"

int sc_main(int sc_argc, char* sc_argv[]) {
	//create an instance of the SystemC module.
	Three_Processes U_Three_Processes("U_Three_Processes");
	cout << "Simulation starts!!" << endl;
	sc_start(100, SC_NS); // invoke the simulator
	return 0;
}