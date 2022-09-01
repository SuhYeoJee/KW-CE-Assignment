#include <systemc.h>
SC_MODULE(Hello_SystemC) { // declare module class
	SC_CTOR(Hello_SystemC) { // create a constructor
		SC_THREAD(main_thread);// register the process
	}//end constructor
	void main_thread(void) {
		cout << " Hello SystemC World!" << endl;
	}
};
int sc_main(int sc_argc, char* sc_argv[]) {
	Hello_SystemC HelloWorld("Hello World");
	sc_start(); // invoke the simulator
	return 0;
}