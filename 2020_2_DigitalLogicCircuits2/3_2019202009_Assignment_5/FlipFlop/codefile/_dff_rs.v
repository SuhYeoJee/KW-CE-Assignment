module _dff_rs(clk,s,r,d,q); //Synchronous set/resettable D flip-flop
	input clk,s,r,d;				// active-low
	output q;
	wire w0,w1,w2;
	
	_or2 U0_or2(.a(d),.b(~s),.y(w0));	//set signal
	_and2 U1_and2(.a(w0),.b(r),.y(w1));	//reset signal
	_dff U2_dff(.clk(clk),.d(w1),.q(q),.qb(w2));
	
endmodule