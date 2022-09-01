#include <systemc.h>

int sc_main(int argc, char* argv[]) {
	// sc_set_time_resolution should be called before 
	// variable declration
	sc_time sc_set_time_resolution(1, SC_PS);
	// Declare the sc_time variables
	sc_time t1(10, SC_NS);
	sc_time t2(5, SC_PS);
	sc_time t3, t4(1, SC_US), t5(1, SC_PS);
	// Print all the variables
	cout << "Value of t1 " << t1.to_string() << endl;
	cout << "Value of t2 " << t2.to_string() << endl;
	cout << "Value of t3 " << t3.to_string() << endl;
	cout << "Value of t4 " << t4.to_string() << endl;
	cout << "Value of t5 " << t5.to_string() << endl;
	// Start the simulation
	cout << "simulation start! " << sc_time_stamp() << endl;
	sc_start(10, SC_PS);
	t3 = sc_time_stamp();
	cout << "Value of t3 " << t3.to_string() << endl;
	sc_start(1, SC_NS);

	t3 = sc_time_stamp();
	cout << "Value of t3 " << t3.to_string() << endl;
	sc_start(20, SC_MS);
	// Get time stamp
	t4 = sc_time_stamp();
	cout << "Value of t4 " << t4.to_string() << endl;
	// sc_time arithmetic examples
	t5 = t4 - t3;
	cout << "Value of t5 " << t5.to_string() << endl;
	if (t5 > t2) {cout << " t5 is greated then t2" << endl;}
	else {cout << " t2 is greated then t5" << endl;	}
	return 1;
}