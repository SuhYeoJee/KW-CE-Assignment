#include <systemc.h>
#include "Three_Process.h"

void Three_Processes::first_thread(void) {
	while (1) {
		wait();
		std::cout << sc_time_stamp() << ": I'm the first thread!" << std::endl;
	}
}
void Three_Processes::second_thread(void) {
	while (1) {
		wait();
		std::cout << sc_time_stamp() << ": I'm the second thread!" << std::endl;
	}
}
void Three_Processes::third_thread(void) {
	while (1) {
		wait();
		std::cout << sc_time_stamp() << ": I'm the third thread!" << std::endl;
	}
}

/*
void Three_Processes::first_thread(void) {
	while (1) {
		wait();
		std::cout << sc_time_stamp() << ": I'm first thread!" << std::endl;
	}
}
void Three_Processes::second_thread(void) {
	while (1) {
		wait();
		wait(SC_ZERO_TIME);
		std::cout << sc_time_stamp() << ": I'm second thread!" << std::endl;
	}
}
void Three_Processes::third_thread(void) {
	while (1) {
		wait();
		wait(SC_ZERO_TIME);
		wait(SC_ZERO_TIME);
		std::cout << sc_time_stamp() << ": I'm third thread!" << std::endl;
	}
}
*/