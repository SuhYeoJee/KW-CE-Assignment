#include "Memory.h"
#include <math.h>
// Constructor definition with arguments
SC_HAS_PROCESS(Memory);
Memory::Memory(sc_module_name instName, int addrW, int dataW) : sc_module(instName) {
	// sizeIn is the size of the memory in KB
	// dataW is the bit width of a data for an address
	addrWidth = addrW; // Address bit width
	dataWidth = dataW; // Data bit width
	//size = ((sc_biguint<MAX>)pow<int, int>(2, addrW)) * (dataW / 8);
	size = ((sc_biguint<64>)pow<int, int>(2, addrW)) * (dataW / 8);
	// Mem size in byte

}