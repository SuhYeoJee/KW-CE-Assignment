module ns_logic(q, ta, tb, d); // next state logic
	input [1:0] q;	// current state
	input ta, tb;	// sensor
	output [1:0] d; //next state
	wire w0,w1;
	
	_xor2 U0_xor2(.a(q[1]),.b(q[0]),.y(d[1]));
	_and3 U1_and3(.a(~q[1]),.b(~q[0]),.c(~ta),.y(w0));
	_and3 U2_and3(.a(q[1]),.b(~q[0]),.c(~tb),.y(w1));
	_or2 U3_or2(.a(w0),.b(w1),.y(d[0]));
	
endmodule