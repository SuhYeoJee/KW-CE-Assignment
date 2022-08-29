module tl_cntr(clk, reset_n, Ta, Tb, La, Lb); // top module
	input clk, reset_n, Ta, Tb; // sensor
	output [1:0] La, Lb; // light
	wire [1:0] wd,wq;
	
	_register2_r_async U0_register2_r_async(.clk(clk),.r(reset_n),.d(wd),.q(wq));
	ns_logic U1_ns_logic(.q(wq),.ta(Ta),.tb(Tb),.d(wd));
	o_logic U2_o_logic(.la(La),.lb(Lb),.q(wq));
	
endmodule