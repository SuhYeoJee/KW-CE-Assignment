module register64_23 (clk, reset_n, en, d_in,
			d_out0, d_out1, d_out2, d_out3, d_out4, d_out5, d_out6, d_out7, d_out8,
			d_out9, d_out10, d_out11, d_out12, d_out13, d_out14, d_out15, d_out16, d_out17,
			d_out18, d_out19, d_out20, d_out21, d_out22);		// [Lab07] 64 bit register * 23
			
	input clk, reset_n;
	input [22:0] en;
	input [63:0] d_in;
	
	output [63:0] d_out0, d_out1, d_out2, d_out3, d_out4, d_out5, d_out6, d_out7, d_out8,
			d_out9, d_out10, d_out11, d_out12, d_out13, d_out14, d_out15, d_out16, d_out17,
			d_out18, d_out19, d_out20, d_out21, d_out22;

	//instance 64 bit register
	register64_r_en U0_register64_r_en(.d_in(d_in),.d_out(d_out0),.en(en[0]),.clk(clk),.reset_n(reset_n));
	register64_r_en U1_register64_r_en(.d_in(d_in),.d_out(d_out1),.en(en[1]),.clk(clk),.reset_n(reset_n));
	register64_r_en U2_register64_r_en(.d_in(d_in),.d_out(d_out2),.en(en[2]),.clk(clk),.reset_n(reset_n));
	register64_r_en U3_register64_r_en(.d_in(d_in),.d_out(d_out3),.en(en[3]),.clk(clk),.reset_n(reset_n));
	register64_r_en U4_register64_r_en(.d_in(d_in),.d_out(d_out4),.en(en[4]),.clk(clk),.reset_n(reset_n));
	register64_r_en U5_register64_r_en(.d_in(d_in),.d_out(d_out5),.en(en[5]),.clk(clk),.reset_n(reset_n));
	register64_r_en U6_register64_r_en(.d_in(d_in),.d_out(d_out6),.en(en[6]),.clk(clk),.reset_n(reset_n));
	register64_r_en U7_register64_r_en(.d_in(d_in),.d_out(d_out7),.en(en[7]),.clk(clk),.reset_n(reset_n));
	register64_r_en U8_register64_r_en(.d_in(d_in),.d_out(d_out8),.en(en[8]),.clk(clk),.reset_n(reset_n));
	register64_r_en U9_register64_r_en(.d_in(d_in),.d_out(d_out9),.en(en[9]),.clk(clk),.reset_n(reset_n));
	
	register64_r_en U10_register64_r_en(.d_in(d_in),.d_out(d_out10),.en(en[10]),.clk(clk),.reset_n(reset_n));
	register64_r_en U11_register64_r_en(.d_in(d_in),.d_out(d_out11),.en(en[11]),.clk(clk),.reset_n(reset_n));
	register64_r_en U12_register64_r_en(.d_in(d_in),.d_out(d_out12),.en(en[12]),.clk(clk),.reset_n(reset_n));
	register64_r_en U13_register64_r_en(.d_in(d_in),.d_out(d_out13),.en(en[13]),.clk(clk),.reset_n(reset_n));
	register64_r_en U14_register64_r_en(.d_in(d_in),.d_out(d_out14),.en(en[14]),.clk(clk),.reset_n(reset_n));
	register64_r_en U15_register64_r_en(.d_in(d_in),.d_out(d_out15),.en(en[15]),.clk(clk),.reset_n(reset_n));
	register64_r_en U16_register64_r_en(.d_in(d_in),.d_out(d_out16),.en(en[16]),.clk(clk),.reset_n(reset_n));
	register64_r_en U17_register64_r_en(.d_in(d_in),.d_out(d_out17),.en(en[17]),.clk(clk),.reset_n(reset_n));
	register64_r_en U18_register64_r_en(.d_in(d_in),.d_out(d_out18),.en(en[18]),.clk(clk),.reset_n(reset_n));
	register64_r_en U19_register64_r_en(.d_in(d_in),.d_out(d_out19),.en(en[19]),.clk(clk),.reset_n(reset_n));
	
	register64_r_en U20_register64_r_en(.d_in(d_in),.d_out(d_out20),.en(en[20]),.clk(clk),.reset_n(reset_n));
	register64_r_en U21_register64_r_en(.d_in(d_in),.d_out(d_out21),.en(en[21]),.clk(clk),.reset_n(reset_n));
	register64_r_en U22_register64_r_en(.d_in(d_in),.d_out(d_out22),.en(en[22]),.clk(clk),.reset_n(reset_n));

endmodule