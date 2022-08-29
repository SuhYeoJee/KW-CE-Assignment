module ha(a,b,s,co); // Half adder module
	input a,b;
	output s,co;
	
	_xor2 S(.a(a),.b(b),.y(s)); // S = a^b
	_and2 CO(.a(a),.b(b),.y(co)); // CO = a&b
endmodule