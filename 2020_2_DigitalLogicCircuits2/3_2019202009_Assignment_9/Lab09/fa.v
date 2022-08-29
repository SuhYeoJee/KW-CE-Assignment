module fa(a,b,ci,s,co); // [Lab02]Full adder
	input a,b,ci; 
	output s,co;
	wire c1,c2,sm;
	
	ha ha1(.a(b),.b(ci),.s(sm),.co(c1)); // s = b^ci, co = b&ci
	ha ha2(.a(a),.b(sm),.s(s),.co(c2)); //s=a^b^ci, co=a&b + a&ci
	_or2 _or(.a(c2),.b(c1),.y(co)); // co = a&b+a&ci+b&ci
endmodule