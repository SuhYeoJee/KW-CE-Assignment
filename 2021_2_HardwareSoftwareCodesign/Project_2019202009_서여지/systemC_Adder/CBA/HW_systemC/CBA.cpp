#include <systemc.h>
#include "CBA.h"

void cba32::cba32_main() {
	sc_int<32> a, b, res;
	sc_int<33> s;
	sc_int<1> CIN, COUT;
	bool set_signal[3], wait_condition[3];

	/////////////////////////////////////////////////////////////
	// A, B, Cin handshake, read
	
	while (1) {

		A_ready.write(1); // set input ready
		B_ready.write(1);
		Cin_ready.write(1);
		set_signal[0] = 0; set_signal[1] = 0; set_signal[2] = 0;
		while (set_signal[0] + set_signal[1] + set_signal[2] < 3) { // A, B, Cin을 모두 읽을 때 까지
			do { // input valid 확인
				wait();
				// valid가 아니거나 이미 set되었으면 wait = true
				wait_condition[0] = ((!A_valid.read()) | set_signal[0]);
				wait_condition[1] = ((!B_valid.read()) | set_signal[1]);
				wait_condition[2] = ((!Cin_valid.read()) | set_signal[2]);
				// A,B,Cin 중 하나라도 wait을 중단하면 break
			} while (wait_condition[0] & wait_condition[1] & wait_condition[2]);

			if (!wait_condition[0]) {
				a = A.read(); // input 읽기
				A_ready.write(0); // set input ready
				set_signal[0] = 1;
			}
			if (!wait_condition[1]) {
				b = B.read(); // input 읽기
				B_ready.write(0); //set input ready
				set_signal[1] = 1;
			}
			if (!wait_condition[2]) {
				CIN = Cin.read(); // input 읽기
				Cin_ready.write(0); //set  input ready
				set_signal[2] = 1;
			}
		}

		/////////////////////////////////////////////////

		// output 계산
		s = (sc_uint<32>)a + (sc_uint<32>)b + (sc_uint<1>)CIN;
		res = s.range(31, 0);
		COUT = s[32];

		// CBA delay
		wait(12);

		/////////////////////////////////////////////////

		// set output valid
		result.write(res);
		Cout.write(COUT);

		result_valid.write(1);
		Cout_valid.write(1);

		set_signal[0] = 0; set_signal[1] = 0;
		while (set_signal[0] + set_signal[1] < 2) { // result, Cout을 모두 전달할 때까지
			do { // output ready 확인
				wait();
				// ready가 아니거나 이미 set되었으면 wait = true
				wait_condition[0] = ((!result_ready.read()) | set_signal[0]);
				wait_condition[1] = ((!Cout_ready.read()) | set_signal[1]);
				// ready, Cout 중 하나라도 wait을 중단하면 break
			} while (wait_condition[0] & wait_condition[1]);

			if (!wait_condition[0]) {
				result_valid.write(0);//set valid
				set_signal[0] = 1;
			}
			if (!wait_condition[1]) {
				Cout_valid.write(0); //set valid
				set_signal[1] = 1;
			}
		}
	}

}