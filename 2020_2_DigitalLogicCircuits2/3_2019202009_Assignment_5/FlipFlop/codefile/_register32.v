module _register32(clk,d,q); //use 4 8 D flip-flop
	input clk;
	input [31:0] d;
	output [31:0] q;
	
	_register8 U0_register8(.d(d[7:0]),.clk(clk),.q(q[7:0]));
	_register8 U1_register8(.d(d[15:8]),.clk(clk),.q(q[15:8]));
	_register8 U2_register8(.d(d[23:16]),.clk(clk),.q(q[23:16]));
	_register8 U3_register8(.d(d[31:24]),.clk(clk),.q(q[31:24]));

endmodule