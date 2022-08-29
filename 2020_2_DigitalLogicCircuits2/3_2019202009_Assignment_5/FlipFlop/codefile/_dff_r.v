module _dff_r(clk,r,d,q); // Resettable D flip-flop
	input clk,r,d;				// active-low
	output q;
	wire w0,w1;
	
	_and2 U0_and2(.a(d),.b(r),.y(w0));	//reset signal
	_dff U1_dff(.clk(clk),.d(w0),.q(q),.qb(w1));
	
endmodule