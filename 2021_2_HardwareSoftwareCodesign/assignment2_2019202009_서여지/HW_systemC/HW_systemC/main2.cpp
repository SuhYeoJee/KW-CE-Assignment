#include <systemc.h>
SC_MODULE(dataType) {
	SC_CTOR(dataType) {
		SC_THREAD(main_thread);
	}
	void main_thread(void) {
		sc_bv<4> addr_bv = "1100";
		sc_bv<8> data_bv;             // data_bv = 00000000
		bool parity_bv;

		cout << "data_bv: " << data_bv << endl;
		data_bv.range(3, 0) = addr_bv; // data_bv = 0000"1100"
		cout << "data_bv: " << data_bv << endl;
		data_bv.range(0, 3) = addr_bv; // data_bv = 0000"0011"
		cout << "data_bv: " << data_bv << endl;
		data_bv[4] = 1;               // data_bv = 000"1"0011
		cout << "data_bv: " << data_bv << endl;
		parity_bv = data_bv.xor_reduce();
		cout << "parity: " << parity_bv << endl << endl << endl;

		///////////////////////////////////////////////////////////////////

		sc_lv<4> data1_lv = "1xz0";
		sc_lv<8> data2_lv;              // data2_lv = xxxxxxxx
		sc_logic parity_lv;

		cout << "data2_lv: " << data2_lv << endl;
		data2_lv.range(3, 0) = data1_lv; // data2_bv = xxxx"1xz0"
		cout << "data2_lv: " << data2_lv << endl;
		data2_lv.range(0, 3) = data1_lv; // data2_bv = xxxx"0zx1"
		cout << "data2_lv: " << data2_lv << endl;
		data2_lv[4] = 1;                // data2_bv = xxx"1"0zx1
		cout << "data2_lv: " << data2_lv << endl;
		parity_lv = data2_lv.xor_reduce();  // parity = x
		cout << "parity: " << parity_lv<<endl;
	}
};
int sc_main(int sc_argc, char* sc_argv[]) {
	dataType datatype("dataType");
	sc_start();
	return 0;
}