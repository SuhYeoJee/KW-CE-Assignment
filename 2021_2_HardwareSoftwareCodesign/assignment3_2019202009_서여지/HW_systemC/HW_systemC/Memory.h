#include <systemc.h>
SC_MODULE(Memory) {
	sc_biguint<200> size;
	int dataWidth, addrWidth;
	// size: Memory size in bytes
	// dataWidth: data bit width
	// addrWidth: address bit width
	Memory(sc_module_name, int, int); // Constructor declaration w/ arguments
	void print() const {
		cout << endl << "Instance name: " << name() << endl
			<< "Memory size is " << size << "bytes."
			<< endl << "Its address and data widths are "
			<< addrWidth << " and " << dataWidth << ", respectively." << endl;
	}
};