#include <systemc.h>
#include "SYSTEM.h"

SYSTEM* top = NULL;

int sc_main(int argc, char* argv[]) {
	top = new SYSTEM("top");
	sc_start(); //SYSTEM module Ω√¿€
	return 0;
}
