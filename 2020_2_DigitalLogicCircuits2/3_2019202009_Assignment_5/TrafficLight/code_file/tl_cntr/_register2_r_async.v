module _register2_r_async(clk,r,d,q); // 2bit register
	input clk, r; // reset: active-low
	input [1:0] d;	//Current state
	output [1:0] q; //Next state
	
	_dff_r_async U0_dff_r_async(.d(d[0]),.clk(clk),.r(r),.q(q[0]));
	_dff_r_async U1_dff_r_async(.d(d[1]),.clk(clk),.r(r),.q(q[1]));
	
endmodule