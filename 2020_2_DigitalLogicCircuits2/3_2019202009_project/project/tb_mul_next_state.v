`timescale 1ns/100ps
module tb_mul_next_state;
	reg state, op_start, op_clear;
	reg [31:0] count;
	wire next_state, op_done;
	
	mul_next_state mul_next_state(state, next_state, op_start, count, op_clear, op_done);
	
	//parameter STEP =10;
	//always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	//clk = 0; 
	op_clear = 0; op_start = 0; state = 1; count = 32'b0;
	#10; op_start = 1;
	#20; count = 32'h0;
	#20; count[31] = 1'b1;
	#20;
	
	//#700; $stop;
	end
endmodule
