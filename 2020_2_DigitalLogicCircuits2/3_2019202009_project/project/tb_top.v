`timescale 1ns/100ps
module tb_top;
	reg clk, reset_n, m_req, m_wr;
	reg [15:0] m_addr;
	reg [31:0] m_dout;
	wire m_grant, interrupt_out;
	wire [63:0] m_din;
	
	top top(clk, reset_n, m_req, m_wr, m_addr, m_dout, m_grant, interrupt_out, m_din);
	
	parameter STEP =20;
	always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
		clk = 0; reset_n=0; m_req=1;
		m_wr = 1;
		m_addr = 16'h0110; m_dout = 32'h00008642; #20;
		m_addr = 16'h0111; m_dout = 32'h00006120; #20;
		m_addr = 16'h0112; m_dout = 32'h00003346; #20;
		m_addr = 16'h0113; m_dout = 32'h00008802; #20;
		m_addr = 16'h0114; m_dout = 32'h00002504; #20;
		m_addr = 16'h0115; m_dout = 32'h00008942; #20;
		m_addr = 16'h0116; m_dout = 32'h00008722; #20;
		m_addr = 16'h0117; m_dout = 32'h00008828; #20;
		m_addr = 16'h0118; m_dout = 32'h00000533; #20;
		m_addr = 16'h0119; m_dout = 32'h00008159; #20;
		m_addr = 16'h0100; m_dout = 32'hfd056c64; #20;
		m_addr = 16'h0101; m_dout = 32'hfd054259; #20;
		m_addr = 16'h0102; m_dout = 32'hfd051f80; #20;
		m_addr = 16'h0103; m_dout = 32'hfd05507e; #20;
		m_addr = 16'h0104; m_dout = 32'hfd058a9a; #20;
		m_addr = 16'h0105; m_dout = 32'hfd052842; #20;
		m_addr = 16'h0106; m_dout = 32'hfd055b2c; #20;
		m_addr = 16'h0107; m_dout = 32'hfd052b5e; #20;
		m_addr = 16'h0108; m_dout = 32'hfd053f65; #20;
		m_addr = 16'h0109; m_dout = 32'hfd057a74; #20;
		m_addr = 16'h0121; m_dout = 32'h00000001; #20;
		m_addr = 16'h0120; m_dout = 32'h00000001;
		wait(interrupt_out == 1'b1); #10; m_wr = 0;
		m_addr = 16'h0100; #20;
		m_addr = 16'h0101; #20;
		m_addr = 16'h0102; #20;
		m_addr = 16'h0103; #20;
		m_addr = 16'h0104; #20;
		m_addr = 16'h0105; #20;
		m_addr = 16'h0106; #20;
		m_addr = 16'h0107; #20;
		m_addr = 16'h0108; #20;
		m_addr = 16'h0109; #20;$stop;
	end
endmodule

