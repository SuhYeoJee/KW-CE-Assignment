module _dff_en(clk,en,d,q); // enabled D flip-flop
	input clk,en,d;
	output q;
	wire w0,w1;
	
	mx2 U0_mx2(.d0(q),.d1(d),.s(en),.y(w0));	// enable signal
	_dff U1_dff(.clk(clk),.d(w0),.q(q),.qb(w1));
	
endmodule