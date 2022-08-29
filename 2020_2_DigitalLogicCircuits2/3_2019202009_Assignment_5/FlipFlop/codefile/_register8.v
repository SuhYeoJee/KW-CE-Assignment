module _register8(clk,d,q); //use 8 D flip-flop
	input clk;
	input [7:0] d;
	output [7:0] q;
	wire [7:0] qb;
	
	_dff U0_ff(.d(d[0]),.clk(clk),.q(q[0]),.qb(qb[0]));
	_dff U1_ff(.d(d[1]),.clk(clk),.q(q[1]),.qb(qb[1]));
	_dff U2_ff(.d(d[2]),.clk(clk),.q(q[2]),.qb(qb[2]));
	_dff U3_ff(.d(d[3]),.clk(clk),.q(q[3]),.qb(qb[3]));
	_dff U4_ff(.d(d[4]),.clk(clk),.q(q[4]),.qb(qb[4]));
	_dff U5_ff(.d(d[5]),.clk(clk),.q(q[5]),.qb(qb[5]));
	_dff U6_ff(.d(d[6]),.clk(clk),.q(q[6]),.qb(qb[6]));
	_dff U7_ff(.d(d[7]),.clk(clk),.q(q[7]),.qb(qb[7]));
	
endmodule