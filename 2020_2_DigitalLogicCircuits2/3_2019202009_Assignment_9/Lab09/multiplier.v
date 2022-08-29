module multiplier(clk, reset_n,multiplier,multiplicand,op_start, op_clear, op_done, result); //[Lab09] Top module
	
	input clk, reset_n, op_start, op_clear;
	input [63:0] multiplier, multiplicand;
	output op_done;
	output [127:0] result;
	wire [1:0] w_cur, w_next; //state
	wire [63:0] w_er, w_nd, w_n_nd, w_cin, w_cout; //multiplicand, counter
	wire [127:0] w_result;
	
	//register
	register64_r reg_multiplier(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(multiplier), .d_out(w_er));
	register64_r reg_multiplicand(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(w_n_nd), .d_out(w_nd));
	register128_r reg_result(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(w_result), .d_out(result));
	register2_r reg_state(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(w_next), .d_out(w_cur));
	register64_r reg_counter(.clk(clk),.reset_n(reset_n),.clear(op_clear),.d_in(w_cin), .d_out(w_cout));
	
	assign op_done = w_cur[1]&w_cur[0]; //op_done
	
	next_state U0(.state(w_cur), .next_state(w_next), .op_start(op_start), .count(w_cout), .op_clear(op_clear));
		
	calculate U1(.multiplier(w_er),.multiplicand(w_nd), .state(w_cur), .o_nd(multiplicand),
		.result(result), .counter(w_cout), .next_m_nd(w_n_nd), .next_counter(w_cin), .next_result(w_result));

endmodule