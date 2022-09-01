#include <systemc.h>

#define inputFile		"./Simulation.txt"	//�Է��� ���� txt����
#define testCase		10					//testcase�� ��, ������ �ݺ��� Ƚ��

SC_MODULE(tb) {
	sc_in< bool > clk;

	sc_out< sc_int<32> > A;
	sc_out<sc_int<1> > A_valid;
	sc_in<sc_int<1> > A_ready;

	sc_out< sc_int<32> > B;
	sc_out<sc_int<1> > B_valid;
	sc_in<sc_int<1> > B_ready;

	sc_out< sc_int<1> > Cin;
	sc_out<sc_int<1> > Cin_valid;
	sc_in<sc_int<1> > Cin_ready;

	sc_in< sc_int<32> > result;
	sc_in<sc_int<1> > result_valid;
	sc_out<sc_int<1> > result_ready;

	sc_in< sc_int<1> > Cout;
	sc_in<sc_int<1> > Cout_valid;
	sc_out<sc_int<1> > Cout_ready;

	sc_int<32> a[testCase], b[testCase];	//Simulation.txt���� ���� �� ����
	sc_int<1> CIN[testCase];

	void source();	//Simulation.txt�� �о� �Է��� �����ϰ�, adder�� �����Ѵ�. 
	void sink();	//adder�� ��� ����� �޾� ����Ѵ�. 

	SC_CTOR(tb) {
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};
