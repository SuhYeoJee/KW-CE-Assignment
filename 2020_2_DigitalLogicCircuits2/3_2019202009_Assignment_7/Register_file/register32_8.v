module register32_8(clk, reset_n, en, d_in, d_out0, d_out1, d_out2, 
						d_out3, d_out4, d_out5, d_out6, d_out7);//32 bit register * 8
	input clk, reset_n;
	input [7:0] en;
	input [31:0] d_in;
	output [31:0] d_out0, d_out1, d_out2, d_out3, d_out4, d_out5, d_out6, d_out7;
	
	//instance 32 bit register
	register32_r_en U0_register32_r_en(.d_in(d_in),.d_out(d_out0),.en(en[0]),.clk(clk),.reset_n(reset_n));
	register32_r_en U1_register32_r_en(.d_in(d_in),.d_out(d_out1),.en(en[1]),.clk(clk),.reset_n(reset_n));
	register32_r_en U2_register32_r_en(.d_in(d_in),.d_out(d_out2),.en(en[2]),.clk(clk),.reset_n(reset_n));
	register32_r_en U3_register32_r_en(.d_in(d_in),.d_out(d_out3),.en(en[3]),.clk(clk),.reset_n(reset_n));
	register32_r_en U4_register32_r_en(.d_in(d_in),.d_out(d_out4),.en(en[4]),.clk(clk),.reset_n(reset_n));
	register32_r_en U5_register32_r_en(.d_in(d_in),.d_out(d_out5),.en(en[5]),.clk(clk),.reset_n(reset_n));
	register32_r_en U6_register32_r_en(.d_in(d_in),.d_out(d_out6),.en(en[6]),.clk(clk),.reset_n(reset_n));
	register32_r_en U7_register32_r_en(.d_in(d_in),.d_out(d_out7),.en(en[7]),.clk(clk),.reset_n(reset_n));
endmodule