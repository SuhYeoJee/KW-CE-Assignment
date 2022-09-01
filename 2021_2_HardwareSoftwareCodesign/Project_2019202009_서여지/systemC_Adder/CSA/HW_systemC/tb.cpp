#include <systemc.h>
#include "tb.h"

void tb::source() {
	//���Ͽ��� ���� ���ڿ� ������ ������ �ٲپ� ����
	sc_int< 32 > aTemp, bTemp;
	char buf1[41], buf2[41];
	FILE* fp;

	if (fopen_s(&fp, inputFile, "rt")) { //���� ����
		cout << "[error]Can't open inputFile" << endl;
		return;
	}
	for(int i = 0 ;i < testCase; i++){	//testCase�� �� ��ŭ �ݺ�
		fgets(buf1, sizeof(buf1), fp);	//A
		fgets(buf2, sizeof(buf2), fp);	//B
		aTemp = 0; bTemp = 0;
		for (int j = 0; j < 39; j++) {	//char* -> int 
			if (buf1[j]=='_') continue;
			aTemp <<= 1; bTemp <<= 1;
			if (buf1[j]=='1') aTemp += 1;
			if (buf2[j]=='1') bTemp += 1;
		}
		this->a[i].range(31,0) = aTemp;	//this�� �迭�� ����
		this->b[i].range(31, 0) = bTemp;

		fgets(buf1, sizeof(buf1), fp);	//CIN
		if (buf1[0] == '1') this->CIN[i] = 1;
		else this->CIN[i] = 0;
		fgets(buf2, sizeof(buf2), fp);	//\n
	}
	fclose(fp);

	bool set_signal[3],		//adder�� A,B,Cin�� �����ߴ��� ����
		wait_condition[3];		//A,B,Cin�� wait ����

	for (int i = 0; i < testCase; i++) {
		A.write(this->a[i]);	//A,B,Cin write
		B.write(this->b[i]);
		Cin.write(this->CIN[i]);

		A_valid.write(1);		//A,B,Cin valid
		B_valid.write(1);
		Cin_valid.write(1);
		set_signal[0] = 0; set_signal[1] = 0, set_signal[2] = 0; //���ŵ��� ����

		// A,B,Cin �� ��� ������ ������
		while (set_signal[0] + set_signal[1] + set_signal[2] < 3) {
			do { // output ready Ȯ��
				wait();
				// adder�� ready�� �ƴϰų� �̹� ���ŵǾ����� adder�� data�� ���� �ʴ´�.(wait = true)
				wait_condition[0] = ((!A_ready.read()) | set_signal[0]);
				wait_condition[1] = ((!B_ready.read()) | set_signal[1]);
				wait_condition[2] = ((!Cin_ready.read()) | set_signal[2]);
				// A,B,Cin �� �ϳ��� wait�� �ߴ��ϸ� break
			} while (wait_condition[0] & wait_condition[1] & wait_condition[2]);
			//adder���� ��ȣ�� ����. 
			if (!wait_condition[0]) {
				A_valid.write(0);//set valid
				set_signal[0] = 1; //���ŵ�
			}
			if (!wait_condition[1]) {
				B_valid.write(0);//set valid
				set_signal[1] = 1;
			}
			if (!wait_condition[2]) {
				Cin_valid.write(0);//set valid
				set_signal[2] = 1;
			}
		}
	}
}

void tb::sink() {
	sc_int< 32 > res;	//adder output
	sc_int< 1 > COUT;	//adder output
	bool wait_condition[2], //result, Cout�� wait ����
		set_signal[2];	//result, Cout ���� ����

	for (int i = 0; i < testCase; i++) {
		result_ready.write(1); // adder�� ����� ���� �� �ִ� ����(ready)
		Cout_ready.write(1);
		set_signal[0] = 0; set_signal[1] = 0; //���ŵ��� ����

		while (set_signal[0] + set_signal[1] < 2) { // result, Cout�� ��� ���� �� ����
			do { // input valid Ȯ��
				wait();
				// valid�� �ƴϰų� �̹� set�Ǿ����� wait = true
				wait_condition[0] = ((!result_valid.read()) | set_signal[0]);
				wait_condition[1] = ((!Cout_valid.read()) | set_signal[1]);
				// result, Cout �� �ϳ��� wait�� �ߴ��ϸ� break
			} while (wait_condition[0] & wait_condition[1]);
			// adder�� ����� ����
			if (!wait_condition[0]) {
				res = result.read(); // input �б�
				result_ready.write(0); // set input ready
				set_signal[0] = 1;	//���ŵ�
			}
			if (!wait_condition[1]) {
				COUT = Cout.read(); // input �б�
				Cout_ready.write(0); //set input ready
				set_signal[1] = 1;
			}
		}
		
		//��� ���
		cout << "Module: CSA[" << sc_time_stamp() << "]" << endl;
		cout << "A: ";
		for (int j = 0; j < 32; j++) {
			if ((!(j % 4)) && j) cout << "_";
			if (this->a[i][31-j] == 1) cout << "1";
			else cout << "0";
		}
		cout << endl;

		cout << "B: ";
		for (int j = 0; j < 32; j++) {
			if ((!(j % 4)) && j) cout << "_";
			if (this->b[i][31 - j] == 1) cout << "1";
			else cout << "0";
		}
		cout << endl;

		cout << "Cin: " << (sc_uint<1>)this->CIN[i].to_int() << endl;
		cout << "Result: ";
		for (int j = 0; j < 32; j++) {
			if ((!(j % 4)) && j) cout << "_";
			if (res[31 - j] == 1) cout << "1";
			else cout << "0";
		}
		cout << endl;
		cout << "Cout: " << (sc_uint<1>)COUT.to_int() << endl<<endl;
	}
	// End simulation
	sc_stop();
}