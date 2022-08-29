`timescale 1ns/100ps
module tb_dff_r;
	reg tb_clk,tb_r,tb_d;
	wire tb_q;

	_dff_r U0_dff_r(.clk(tb_clk),.r(tb_r),.d(tb_d),.q(tb_q));			
	
	parameter STEP =10;
	always #(STEP/3) tb_clk = ~tb_clk; //clk changes every 10/3 ns
	always #(STEP/2) tb_d = ~tb_d;		// data changes every 5ns
	
	initial begin
	tb_clk = 0; tb_r=0; tb_d = 0; //reset signal works (active low)
	#10; tb_r=1;
	#40; tb_r=0; //reset signal works (active low)
	#30; $stop;
	end
endmodule