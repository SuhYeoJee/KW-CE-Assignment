module register8_r_en(clk, reset_n, en, d_in, d_out); //[Lab05]resettable, enabled 8bit register
	input clk, reset_n, en;
	input [7:0] d_in;
	output [7:0] d_out;
	
	//instance resettable/enabled d flip-flop
	_dff_r_en U0_dff_r_en(.d(d_in[0]),.q(d_out[0]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U1_dff_r_en(.d(d_in[1]),.q(d_out[1]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U2_dff_r_en(.d(d_in[2]),.q(d_out[2]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U3_dff_r_en(.d(d_in[3]),.q(d_out[3]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U4_dff_r_en(.d(d_in[4]),.q(d_out[4]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U5_dff_r_en(.d(d_in[5]),.q(d_out[5]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U6_dff_r_en(.d(d_in[6]),.q(d_out[6]),.en(en),.clk(clk),.reset_n(reset_n));
	_dff_r_en U7_dff_r_en(.d(d_in[7]),.q(d_out[7]),.en(en),.clk(clk),.reset_n(reset_n));
endmodule