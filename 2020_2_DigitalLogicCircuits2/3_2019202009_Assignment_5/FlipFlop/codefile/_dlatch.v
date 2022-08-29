module _dlatch(clk,d,q,qb); //D Latch
	input clk,d;
	output q,qb;
	wire w0,w1;
	
	_and2 U0_and2(.a(clk),.b(~d),.y(w0));	// use 2 2AND to Data signal
	_and2 U1_and2(.a(clk),.b(d),.y(w1));
	_srlatch U2_srlatch(.r(w0),.s(w1),.q(q),.qb(qb)); // SR Latch
	
endmodule