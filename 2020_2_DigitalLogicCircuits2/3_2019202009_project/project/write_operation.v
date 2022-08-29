module write_operation(Addr, we, to_reg); //[Lab07] find register
	input we;
	input [15:0] Addr;
	output [22:0] to_reg;
	wire [22:0] w;
	
	//instance
	_4_to_23_decoder U0_decoder(.d(Addr),.q(w));
	assign to_reg[0] = we & w[0];
	assign to_reg[1] = we & w[1];
	assign to_reg[2] = we & w[2];
	assign to_reg[3] = we & w[3];
	assign to_reg[4] = we & w[4];
	assign to_reg[5] = we & w[5];
	assign to_reg[6] = we & w[6];
	assign to_reg[7] = we & w[7];
	assign to_reg[8] = we & w[8];
	assign to_reg[9] = we & w[9];
	assign to_reg[10] = we & w[10];
	assign to_reg[11] = we & w[11];
	assign to_reg[12] = we & w[12];
	assign to_reg[13] = we & w[13];
	assign to_reg[14] = we & w[14];
	assign to_reg[15] = we & w[15];
	assign to_reg[16] = we & w[16];
	assign to_reg[17] = we & w[17];
	assign to_reg[18] = we & w[18];
	assign to_reg[19] = we & w[19];
	assign to_reg[20] = we & w[20];
	assign to_reg[21] = we & w[21];
	assign to_reg[22] = we & w[22];
endmodule