module write_operation(Addr, we, to_reg); //[LAB06]find register
	input we;
	input [2:0] Addr;
	output [7:0] to_reg;
	wire [7:0] w;
	
	//instance
	_3_to_8_decoder U0_3_to_8_decoder(.d(Addr),.q(w));
	_and2 U1_and2(.a(we),.b(w[0]),.y(to_reg[0]));
	_and2 U2_and2(.a(we),.b(w[1]),.y(to_reg[1]));
	_and2 U3_and2(.a(we),.b(w[2]),.y(to_reg[2]));
	_and2 U4_and2(.a(we),.b(w[3]),.y(to_reg[3]));
	_and2 U5_and2(.a(we),.b(w[4]),.y(to_reg[4]));
	_and2 U6_and2(.a(we),.b(w[5]),.y(to_reg[5]));
	_and2 U7_and2(.a(we),.b(w[6]),.y(to_reg[6]));
	_and2 U8_and2(.a(we),.b(w[7]),.y(to_reg[7]));
endmodule