`timescale 1ns/100ps //too many pin << [179000]
module tb_mul_calculate;
	reg cur_state, op_start;
	reg [7:0] multiplier, multiplicand, cur_counter, cur_multiplicand;
	reg [15:0] cur_result;
	wire [7:0] next_multiplicand, next_counter;
	wire [15:0] next_result;
	reg [7:0] w_result;
	wire [7:0] w_add, w_sub;
	
	mul_calculate(op_start, multiplier, multiplicand, cur_state,  cur_multiplicand, cur_result, cur_counter, 
							next_multiplicand, next_result, next_counter); 
	
	//parameter STEP =10;
	//always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	//clk = 0; 
	op_start=0; multiplier=8'h34; multiplicand=8'b0011;
	cur_state=0;  cur_multiplicand=0; cur_result=0; cur_counter=0;
	#10; op_start = 1;
	#10; cur_state = 1; cur_multiplicand = 8'b0011;cur_counter = 1;
	#20; 
	
	//#700; $stop;
	end
endmodule
