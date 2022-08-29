module register64_r_en(clk, reset_n, en, d_in, d_out);//[Lab05] 64 bit register (resettable, enabled)
	input clk, reset_n, en;
	input [63:0] d_in;
	output [63:0] d_out;
	
	//instance 8 bit regiser
	register8_r_en U0_register8_r_en(.d_in(d_in[7:0]),.d_out(d_out[7:0]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U1_register8_r_en(.d_in(d_in[15:8]),.d_out(d_out[15:8]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U2_register8_r_en(.d_in(d_in[23:16]),.d_out(d_out[23:16]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U3_register8_r_en(.d_in(d_in[31:24]),.d_out(d_out[31:24]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U4_register8_r_en(.d_in(d_in[39:32]),.d_out(d_out[39:32]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U5_register8_r_en(.d_in(d_in[47:40]),.d_out(d_out[47:40]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U6_register8_r_en(.d_in(d_in[55:48]),.d_out(d_out[55:48]),.en(en),.clk(clk),.reset_n(reset_n));
	register8_r_en U7_register8_r_en(.d_in(d_in[63:56]),.d_out(d_out[63:56]),.en(en),.clk(clk),.reset_n(reset_n));
endmodule