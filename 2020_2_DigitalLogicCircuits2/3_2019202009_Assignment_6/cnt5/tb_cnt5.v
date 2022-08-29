`timescale 1ns/100ps
module tb_cnt5;
	reg tb_inc, tb_clk,tb_reset_n;
	wire [2:0] tb_cnt;
	
	cnt5	U0_cnt5(.cnt(tb_cnt),.clk(tb_clk),.reset_n(tb_reset_n),.inc(tb_inc));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=1; tb_inc = 0;
	#3; tb_reset_n=0; //reset signal works (active low)
	#5; tb_reset_n=1; tb_inc=1;
	#15; tb_inc=0;
	#10; tb_inc=1;
	#5; tb_inc=0;
	#50; $stop;
	end
endmodule