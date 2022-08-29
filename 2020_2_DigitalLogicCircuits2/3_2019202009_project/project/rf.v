module rf(clk, reset_n, Addr, wData, we, rData);//[Lab07] register file
	input clk, reset_n, we;
	input [15:0] Addr;
	input [63:0] wData;
	output [63:0] rData;
	wire [22:0] to_reg;
	wire [63:0] from_reg[0:22];
	
	register64_23 U0_register23(.clk(clk), .reset_n(reset_n), .en(to_reg), .d_in(wData),
			.d_out0(from_reg[0]), .d_out1(from_reg[1]), .d_out2(from_reg[2]), .d_out3(from_reg[3]),
			.d_out4(from_reg[4]), .d_out5(from_reg[5]), .d_out6(from_reg[6]), .d_out7(from_reg[7]),
			.d_out8(from_reg[8]), .d_out9(from_reg[9]), .d_out10(from_reg[10]), .d_out11(from_reg[11]),
			.d_out12(from_reg[12]), .d_out13(from_reg[13]), .d_out14(from_reg[14]), .d_out15(from_reg[15]),
			.d_out16(from_reg[16]), .d_out17(from_reg[17]), .d_out18(from_reg[18]), .d_out19(from_reg[19]),
			.d_out20(from_reg[20]), .d_out21(from_reg[21]), .d_out22(from_reg[22]));
	
	write_operation U1_write(.Addr(Addr), .we(we), .to_reg(to_reg));

	read_operation U2_read_operation(.clk(clk), .Addr(Addr), .Data(rData), 
			.from_reg0(from_reg[0]), .from_reg1(from_reg[1]), .from_reg2(from_reg[2]),.from_reg3(from_reg[3]), 
			.from_reg4(from_reg[4]), .from_reg5(from_reg[5]), .from_reg6(from_reg[6]), .from_reg7(from_reg[7]),
			.from_reg8(from_reg[8]), .from_reg9(from_reg[9]), .from_reg10(from_reg[10]), .from_reg11(from_reg[11]),
			.from_reg12(from_reg[12]), .from_reg13(from_reg[13]), .from_reg14(from_reg[14]), .from_reg15(from_reg[15]),
			.from_reg16(from_reg[16]), .from_reg17(from_reg[17]), .from_reg18(from_reg[18]), .from_reg19(from_reg[19]),
			.from_reg20(from_reg[20]), .from_reg21(from_reg[21]), .from_reg22(from_reg[22]) );
endmodule