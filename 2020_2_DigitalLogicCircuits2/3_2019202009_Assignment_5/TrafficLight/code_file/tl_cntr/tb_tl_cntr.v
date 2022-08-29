`timescale 1ns/100ps
module tb_tl_cntr;
	reg tb_clk,tb_reset_n,tb_Ta, tb_Tb;
	wire [1:0] tb_La, tb_Lb;

	tl_cntr U0_tl_cntr(.clk(tb_clk),.reset_n(tb_reset_n),
				.Ta(tb_Ta),.Tb(tb_Tb),.La(tb_La),.Lb(tb_Lb));
			
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=1; tb_Ta = 0; tb_Tb=0; 
	#3; tb_reset_n=0; //reset signal works (active low)
	#5; tb_reset_n=1; tb_Ta=1; //Academic Ave sensor
	#15; tb_Ta=0;
	#60; tb_Tb=1;
	#15; tb_Tb=0;
	#20; $stop;
	end
endmodule