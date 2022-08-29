module top(clk, reset_n, m_req, m_wr, m_addr, m_dout, m_grant, interrupt_out, m_din); //[project] mini processor top module
	input clk, reset_n, m_req, m_wr;
	input [15:0] m_addr;
	input [31:0] m_dout;
	output m_grant, interrupt_out;
	output [63:0] m_din;
	
	wire s_wr, s_sel;
	wire [15:0] s_addr;
	wire [63:0] s_din,s_dout;
	
	mp mp(.clk(clk), .reset_n(reset_n), .s_wr(s_wr), .s0_sel(s_sel), .s_addr(s_addr), .s_din(s_din[31:0]), .interrupt_out(interrupt_out), .s_dout(s_dout));
	
	bus bus(.clk(clk), .reset_n(reset_n), .m_req(m_req), .m_wr(m_wr), .m_addr(m_addr), .m_dout(m_dout), .s_dout(s_dout),
				.m_grant(m_grant), .m_din(m_din), .s_addr(s_addr), .s_wr(s_wr), .s_din(s_din), .s_sel(s_sel));	
endmodule