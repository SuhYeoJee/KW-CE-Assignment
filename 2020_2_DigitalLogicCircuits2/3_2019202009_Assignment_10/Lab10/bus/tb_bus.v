`timescale 1ns/100ps
module tb_bus;
	reg tb_clk, reset_n, m0_req, m0_wr, m1_req, m1_wr;
	reg [7:0] m0_address, m1_address;
	reg [31:0] m0_dout, m1_dout, s0_dout, s1_dout;
	wire m0_grant, m1_grant, s0_sel, s1_sel,s_wr;
	wire [7:0] s_address;
	wire [31:0] m_din, s_din;
	
	bus U0(.clk(tb_clk), .reset_n(reset_n), .m0_req(m0_req), .m0_wr(m0_wr), .m0_address(m0_address), .m0_dout(m0_dout),
		.m1_req(m1_req), .m1_wr(m1_wr), .m1_address(m1_address), .m1_dout(m1_dout), .s0_dout(s0_dout), .s1_dout(s1_dout),
		.m0_grant(m0_grant), .m1_grant(m1_grant), .m_din(m_din), .s0_sel(s0_sel), .s1_sel(s1_sel), .s_address(s_address), .s_wr(s_wr), .s_din(s_din));
		
			
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 1'b0; reset_n = 0; m0_req = 0; m0_wr = 0; m1_req = 0; m1_wr = 0;
	m0_address = 8'b0; m1_address = 8'b0; m0_dout = 32'b0; m1_dout = 32'b0; s0_dout = 32'b0; s1_dout = 32'b0;
	
	#8; reset_n = 1; m1_req = 1; m1_wr = 1; m1_address = 8'h03; m1_dout = 32'hFFFF_FFFF; //m1 write
	#20; m1_address = 8'h21; m1_dout = 32'h1234_5678; //m1 write
	#20; m0_req = 1; m0_wr=0; m0_address = 8'h13; m1_wr = 0;s0_dout = 32'h5555_5555;s1_dout = 32'h3333_3333; //m1 read
	#20; m1_req = 0; //m2 read
	#40; $stop;
	end
endmodule
