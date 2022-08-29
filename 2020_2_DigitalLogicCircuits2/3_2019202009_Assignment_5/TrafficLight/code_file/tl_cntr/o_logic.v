module o_logic(la,lb,q); // output logic
	input [1:0] q;	// state
	output [1:0] la, lb; //light
	
	assign la[1] = q[1];
	_and2 U0_and2(.a(~q[1]),.b(q[0]),.y(la[0]));
	assign lb[1] = ~q[1];
	_and2 U1_and2(.a(q[1]),.b(q[0]),.y(lb[0]));
	
endmodule