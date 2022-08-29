module _dff(clk,d,q,qb); //D flip-flop
	input clk,d;
	output q,qb;
	wire w0,w1;
	
	_dlatch U0_dlatch(.d(d),.clk(~clk),.q(w0),.qb(w1)); //use 2 D Latch
	_dlatch U1_dlatch(.d(w0),.clk(clk),.q(q),.qb(qb));
	
endmodule