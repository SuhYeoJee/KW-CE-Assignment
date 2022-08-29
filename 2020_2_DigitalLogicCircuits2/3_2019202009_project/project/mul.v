module mul(clk, reset_n, op_start, op_clear, multiplier, multiplicand, op_done, result, cur_state, cur_multiplicand); //[Lab09] Multiplier
	input clk, reset_n, op_start, op_clear;
	input [31:0] multiplier, multiplicand;
	output op_done;
	output [63:0] result;
	//wire cur_state, next_state; //state
	output[1:0] cur_state;
	wire[1:0] next_state;
	//wire [31:0] w_multiplier, cur_multiplicand, next_multiplicand, next_counter, cur_counter; //multiplicand, counter
	output [31:0] cur_multiplicand;
	wire [31:0] w_multiplier, next_multiplicand, next_counter, cur_counter;
	wire [63:0] w_result;
	
	//register
	register32_r reg_multiplier(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(multiplier), .d_out(w_multiplier));
	register32_r reg_multiplicand(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(next_multiplicand), .d_out(cur_multiplicand));
	register64_r reg_result(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(w_result), .d_out(result));
	register2_r  reg_state(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(next_state), .d_out(cur_state));
	register32_r reg_counter(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(next_counter), .d_out(cur_counter));
	
	//assign op_done = cur_state & cur_counter[31]; //op_done
	
	mul_next_state mul_next_state(.state(cur_state), .next_state(next_state), .op_start(op_start), .count(cur_counter), .op_clear(op_clear), .op_done(op_done));	
	
	mul_calculate mul_calculate(.op_start(op_start), .multiplier(w_multiplier), .multiplicand(multiplicand), .cur_state(cur_state), 
						.cur_multiplicand(cur_multiplicand), .cur_result(result), .cur_counter(cur_counter), 
						.next_multiplicand(next_multiplicand), .next_result(w_result), .next_counter(next_counter));
endmodule