module tl_cntr_w_left(clk, reset_n, Ta, Tal, Tb, Tbl, La, Lb); // top module
	input clk, reset_n, Ta, Tal, Tb, Tbl; // sensor
	output [1:0] La, Lb; // light
	wire [2:0] wd,wq;
	
	_register3_r U0_register3_r(.clk(clk),.r(reset_n),.d(wd),.q(wq));
	ns_logic U1_ns_logic(.q(wq),.ta(Ta),.tal(Tal),.tb(Tb),.tbl(Tbl),.d(wd));
	o_logic U2_o_logic(.la(La),.lb(Lb),.q(wq));
	
endmodule