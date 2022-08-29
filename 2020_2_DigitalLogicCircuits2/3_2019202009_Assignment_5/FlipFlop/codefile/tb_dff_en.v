`timescale 1ns/100ps
module tb_dff_en;
	reg tb_clk,tb_en,tb_d;
	wire tb_q;

	_dff_en U0_dff_en(.clk(tb_clk),.en(tb_en),.d(tb_d),.q(tb_q));			
	
	parameter STEP =10;
	always #(STEP/3) tb_clk = ~tb_clk; // clk changes every 10/3 ns
	always #(STEP/2) tb_d = ~tb_d; //data changes every 5ns
	
	initial begin
	tb_clk = 0; tb_en=1; tb_d = 0;
	#40; tb_en=0; // enable change.
	#40; $stop;
	end
endmodule