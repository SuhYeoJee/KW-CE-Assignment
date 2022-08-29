`timescale 1ns/100ps
module tb_dff_rs;
	reg tb_clk, tb_r, tb_s,tb_d;
	wire tb_q;

	_dff_rs U0_dff_rs(.clk(tb_clk),.r(tb_r),.s(tb_s),.d(tb_d),.q(tb_q));			
	
	parameter STEP =20;
	always #(STEP/5) tb_clk = ~tb_clk; //clk changes every 4 ns
	always #(STEP/3) tb_d = ~tb_d; //data changes every 20/3 ns
	
	initial begin
	tb_clk = 0; tb_r=0; tb_s=0; tb_d = 0; //reset,set signal works (active low)
	#20; tb_r=1;		//set signal works
	#20; tb_s=1;		//no reset,set signal
	#20; tb_r=0;		//reset signal works
	#20; $stop;
	end
endmodule