module _register8_r(clk, reset_n, d, q);// 8bit register
	input clk, reset_n;
	input [7:0] d;
	output [7:0] q;
	
	//instance register
	_dff_r U0_dff_r(.d(d[0]),.q(q[0]),.clk(clk),.reset_n(reset_n));
	_dff_r U1_dff_r(.d(d[1]),.q(q[1]),.clk(clk),.reset_n(reset_n));
	_dff_r U2_dff_r(.d(d[2]),.q(q[2]),.clk(clk),.reset_n(reset_n));
	_dff_r U3_dff_r(.d(d[3]),.q(q[3]),.clk(clk),.reset_n(reset_n));
	_dff_r U4_dff_r(.d(d[4]),.q(q[4]),.clk(clk),.reset_n(reset_n));
	_dff_r U5_dff_r(.d(d[5]),.q(q[5]),.clk(clk),.reset_n(reset_n));
	_dff_r U6_dff_r(.d(d[6]),.q(q[6]),.clk(clk),.reset_n(reset_n));
	_dff_r U7_dff_r(.d(d[7]),.q(q[7]),.clk(clk),.reset_n(reset_n));
endmodule