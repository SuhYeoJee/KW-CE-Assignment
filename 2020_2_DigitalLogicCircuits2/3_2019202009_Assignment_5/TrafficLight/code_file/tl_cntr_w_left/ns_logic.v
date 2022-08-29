module ns_logic(q, ta, tal, tb, tbl, d); // next state logic
	input [2:0] q;	// current state
	input ta,tal, tb, tbl;	// sensor
	output [2:0] d; //next state
	wire [8:0] w;
	
	//d[2] = Q2'Q1Q0 + Q2Q1Q0' + Q2Q1'
	_and3 U0_and3(.a(~q[2]),.b(q[1]),.c(q[0]),.y(w[0]));
	_and3 U1_and3(.a(q[2]),.b(q[1]),.c(~q[0]),.y(w[1]));
	_and2 U2_and2(.a(q[2]),.b(~q[1]),.y(w[2]));
	_or3 U3_or3(.a(w[0]),.b(w[1]),.c(w[2]),.y(d[2]));
	
	//d[1] = Q1'Q0 + Q1 Q0'
	_and2 U4_and2(.a(~q[1]),.b(q[0]),.y(w[3]));
	_and2 U5_and2(.a(q[1]),.b(~q[0]),.y(w[4]));
	_or2 U6_or2(.a(w[3]),.b(w[4]),.y(d[1]));
	
	//d[0] = Q2'Q1'Q0'TA' + Q2'Q1Q0'TAL' + Q2Q1Q0'TBL' + Q2Q1'Q0'TB'
	_and4 U7_and4(.a(~q[2]),.b(!q[1]),.c(~q[0]), .d(~ta),.y(w[5]));
	_and4 U8_and4(.a(~q[2]),.b(q[1]),.c(~q[0]), .d(~tal),.y(w[6]));
	_and4 U9_and4(.a(q[2]),.b(q[1]),.c(~q[0]), .d(~tbl),.y(w[7]));
	_and4 U10_and4(.a(q[2]),.b(~q[1]),.c(~q[0]), .d(~tb),.y(w[8]));
	_or4 U11_or4(.a(w[5]),.b(w[6]),.c(w[7]),.d(w[8]),.y(d[0]));
	
endmodule