module _inv(a,y); //inverter module
	input a;
	output y;
	assign y=~a;
endmodule

module _nand2(a,b,y); //NAND module
	input a,b;
	output y;
	assign y=~(a&b);
endmodule

module _and2(a,b,y); //AND module
	input a,b;
	output y;
	assign y=a&b;
endmodule

module _or2(a,b,y); //OR module
	input a,b;
	output y;
	assign y=a|b;
endmodule

module _xor2(a,b,y); //XOR module
	input a,b;
	output y;
	wire inv_a,inv_b;
	wire w0, w1;
	
	_inv INV1(.a(a),.y(inv_a));
	_inv INV2(.a(b),.y(inv_b));
	_and2 AND1(.a(a),.b(inv_b),.y(w0));
	_and2 AND2(.a(inv_a),.b(b),.y(w1));
	_or2 OR1(.a(w0),.b(w1),.y(y));
endmodule