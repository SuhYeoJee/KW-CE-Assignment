`timescale 1ns/100ps
module tb_dff;
	reg tb_clk,tb_d;
	wire tb_q, tb_qb;

	_dff U0_dff(.clk(tb_clk),.d(tb_d),.q(tb_q),.qb(tb_qb));			
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; // clk changes every 5ns
	
	initial begin
	tb_clk = 0; tb_d = 0;	
	#8; tb_d = 1;
	#8; tb_d = 0;
	#2; tb_d = 1;
	#4; tb_d = 0;
	#2; tb_d = 1;
	#10; $stop;
	end
endmodule