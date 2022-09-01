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
		while (set_signal[0] + set_signal[1] + set_signal[2] < 3) { // A, B, Cin�� ��� ���� �� ����
			do { // input valid Ȯ��
				wait();
				// valid�� �ƴϰų� �̹� set�Ǿ����� wait = true
				wait_condition[0] = ((!A_valid.read()) | set_signal[0]);
				wait_condition[1] = ((!B_valid.read()) | set_signal[1]);
				wait_condition[2] = ((!Cin_valid.read()) | set_signal[2]);
				// A,B,Cin �� �ϳ��� wait�� �ߴ��ϸ� break
			} while (wait_condition[0] & wait_condition[1] & wait_condition[2]);

			if (!wait_condition[0]) {
				a = A.read(); // input �б�
				A_ready.write(0); // set input ready
				set_signal[0] = 1;
			}
			if (!wait_condition[1]) {
				b = B.read(); // input �б�
				B_ready.write(0); //set input ready
				set_signal[1] = 1;
			}
			if (!wait_condition[2]) {
				CIN = Cin.read(); // input �б�
				Cin_ready.write(0); //set  input ready
				set_signal[2] = 1;
			}
		}

		/////////////////////////////////////////////////

		// output ���
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
		while (set_signal[0] + set_signal[1] < 2) { // result, Cout�� ��� ������ ������
			do { // output ready Ȯ��
				wait();
				// ready�� �ƴϰų� �̹� set�Ǿ����� wait = true
				wait_condition[0] = ((!result_ready.read()) | set_signal[0]);
				wait_condition[1] = ((!Cout_ready.read()) | set_signal[1]);
				// ready, Cout �� �ϳ��� wait�� �ߴ��ϸ� break
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