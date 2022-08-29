`timescale 1ns/100ps
module tb_multiplier;
	reg tb_clk, tb_reset_n, tb_op_start, tb_op_clear;
	reg [63:0] tb_multiplier, tb_multiplicand;
	wire tb_op_done;
	wire [127:0] tb_result;
	
	multiplier U0_multiplier(.clk(tb_clk), .reset_n(tb_reset_n),.op_start(tb_op_start),
		.op_clear(tb_op_clear),.multiplier(tb_multiplier),.multiplicand(tb_multiplicand),
		.op_done(tb_op_done),.result(tb_result));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 0; tb_reset_n=0; tb_op_start=0; tb_op_clear = 0;
	#28;	tb_reset_n=1;tb_multiplicand = 64'b0111;tb_multiplier = 64'hFFFF_FFFF_FFFF_FFF9; // 7*-7
	#15; tb_op_start=1; 
	// #50; tb_op_clear = 1; //op_clear test
	#700; $stop;
	end
endmodule
