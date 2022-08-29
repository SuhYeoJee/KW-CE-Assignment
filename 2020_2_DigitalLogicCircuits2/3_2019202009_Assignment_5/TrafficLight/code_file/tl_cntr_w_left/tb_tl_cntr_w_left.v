`timescale 1ns/100ps
module tb_tl_cntr_w_left;
	reg tb_clk,tb_reset_n,tb_Ta,tb_Tal,tb_Tb,tb_Tbl;
	wire [1:0] tb_La, tb_Lb;

	tl_cntr_w_left U0_tl_cntr_w_left(.clk(tb_clk),.reset_n(tb_reset_n),
				.Ta(tb_Ta),.Tal(tb_Tal),.Tb(tb_Tb),.Tbl(tb_Tbl),.La(tb_La),.Lb(tb_Lb));
			
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=1; tb_Ta = 0; tb_Tal=0; tb_Tb=0; tb_Tbl=0; 
	#3; tb_reset_n=0; //reset signal works (active low)
	#5; tb_reset_n=1; tb_Ta=1; tb_Tal=1; //Academic Ave sensor
	#15; tb_Ta=0;
	#30; tb_Tal=0;
	#10; tb_Tb=1;
	#15; tb_Tb=0;
	#50; $stop;
	end
endmodule