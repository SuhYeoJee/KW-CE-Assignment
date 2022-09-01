#include <systemc.h>

#define inputFile		"./Simulation.txt"	//입력이 적힌 txt파일
#define testCase		10					//testcase의 수, 덧셈을 반복할 횟수

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

	sc_int<32> a[testCase], b[testCase];	//Simulation.txt에서 읽은 값 저장
	sc_int<1> CIN[testCase];

	void source();	//Simulation.txt를 읽어 입력을 생성하고, adder에 전달한다. 
	void sink();	//adder의 계산 결과를 받아 출력한다. 

	SC_CTOR(tb) {
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};
