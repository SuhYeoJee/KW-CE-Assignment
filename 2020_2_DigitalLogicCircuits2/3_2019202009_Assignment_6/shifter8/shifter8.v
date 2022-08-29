module shifter8(clk, reset_n, op, shamt, d_in, d_out); //top module
	input	clk, reset_n;
	input [2:0] op;
	input [1:0] shamt;
	input [7:0] d_in;
	output [7:0] d_out;
	wire [7:0] d_next;
	
	_register8_r U0_register8_r(.d(d_next), .q(d_out),.clk(clk),.reset_n(reset_n));
	cc_logic U1_cc_logic(.op(op),.shamt(shamt),.d_in(d_in),.d_out(d_out),.d_next(d_next));
endmodule