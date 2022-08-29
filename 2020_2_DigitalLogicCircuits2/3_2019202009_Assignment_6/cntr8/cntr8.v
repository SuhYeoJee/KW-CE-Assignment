module cntr8(clk, reset_n, inc, load, d_in, d_out, o_state); //8 bit counter
	input clk, reset_n, inc, load;	//loadable, up/down
	input [7:0] d_in;
	output [7:0] d_out;
	output [2:0] o_state;
	wire [2:0] next_state, state;
	
	assign o_state = state;
	_register3_r U0_register_r(.d(next_state),.q(state),.clk(clk),.reset_n(reset_n));
	ns_logic U1_ns_logic(.state(state), .next_state(next_state),.inc(inc),.load(load));
	os_logic U2_os_logic(.state(state),.d_in(d_in),.d_out(d_out));
endmodule