`timescale 1ns/100ps
module tb_bus;
	reg clk, reset_n, m_req, m_wr;
	reg [15:0] m_addr; // 0x0100 ~ 0x1ff
	reg [63:0] m_dout, s_dout;
	wire s_sel;
	wire s_wr, m_grant;
	wire [15:0] s_addr;
	wire [63:0] m_din, s_din;

	bus bus(clk, reset_n, m_req, m_wr, m_addr, m_dout, s_dout,
				m_grant, m_din, s_addr, s_wr, s_din, s_sel);//[Lab10] bus
	
	parameter STEP =10;
	always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
	clk = 1'b0; reset_n = 0; m_req = 0; m_wr = 0; 
	m_addr = 8'b0; m_dout = 32'b0; s_dout = 32'b0;
	
	#8; reset_n = 1; m_req = 1; m_wr = 1; m_addr = 16'h0100; m_dout = 64'hFFFF_FFFF; //m write
	#20; m_addr = 16'h0110; m_dout = 32'h1234_5678; //m write
	#20; m_wr=0; m_addr = 16'h0000; m_wr = 0;s_dout = 32'h5555_5555; //m1 read
	#20; reset_n = 0;m_req = 0;
	#10; reset_n = 1;m_req = 1;m_addr = 16'h0100;
	#40; $stop;
	end
endmodule
