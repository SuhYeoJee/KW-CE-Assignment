module _register3_r(clk,reset_n,d,q); // 3 bit register
	input clk, reset_n; // reset: active-low
	input [2:0] d;	//Current state
	output [2:0] q; //Next state
	
	//instance resettable d flip-flop
	_dff_r U0_dff_r(.clk(clk),.reset_n(reset_n),.d(d[0]),.q(q[0]));
	_dff_r U1_dff_r(.clk(clk),.reset_n(reset_n),.d(d[1]),.q(q[1]));
	_dff_r U2_dff_r(.clk(clk),.reset_n(reset_n),.d(d[2]),.q(q[2]));
endmodule