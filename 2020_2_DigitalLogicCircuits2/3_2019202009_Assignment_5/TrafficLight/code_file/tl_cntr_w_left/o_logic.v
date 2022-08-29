module o_logic(la,lb,q); // output logic
	input [2:0] q;	// state
	output [1:0] la, lb; //light
	wire w;
	
	_and2 U0_and2(.a(q[1]),.b(~q[0]),.y(w));
	_or2 U1_or2(.a(q[2]),.b(w),.y(la[1])); 		//LA1 = Q2 + Q1Q0'
	_or2 U2_or2(.a(q[2]),.b(q[0]),.y(la[0]));		//LA0 = Q2 + Q0
	_or2 U3_or2(.a(~q[2]),.b(w),.y(lb[1]));		//LB1 = Q2' + Q1Q0'
	_or2 U4_or2(.a(~q[2]),.b(q[0]),.y(lb[0]));	//LB0 = Q2' + Q0

endmodule