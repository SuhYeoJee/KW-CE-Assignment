`timescale 1ns/100ps
module tb_mul;
	reg clk, reset_n, op_start, op_clear;
	reg [31:0] multiplier, multiplicand;
	wire op_done, cur_state;
	wire [31:0] cur_multiplicand;
	wire [63:0] result;
	
	mul mul(clk, reset_n, op_start, op_clear, multiplier, multiplicand, op_done, result, cur_state, cur_multiplicand); //[Lab09] Multiplier
	
	parameter STEP =10;
	always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
	clk = 0; reset_n=0; op_start=0; op_clear = 0;
	#28;	reset_n=1; multiplicand = 32'b0111; multiplier = 32'hFFFF_FFF9; // 7*-7
	#15; 	op_start=1; 
	#700; $stop;
	end
endmodule
