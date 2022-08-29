module _register3_r(clk,r,d,q); // 3 bit register
	input clk, r; // reset: active-low
	input [2:0] d;	//Current state
	output [2:0] q; //Next state
	
	_dff_r_async U0_dff_r_async(.d(d[0]),.clk(clk),.r(r),.q(q[0]));
	_dff_r_async U1_dff_r_async(.d(d[1]),.clk(clk),.r(r),.q(q[1]));
	_dff_r_async U2_dff_r_async(.d(d[2]),.clk(clk),.r(r),.q(q[2]));
endmodule