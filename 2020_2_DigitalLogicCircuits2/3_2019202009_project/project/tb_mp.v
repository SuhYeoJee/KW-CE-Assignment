`timescale 1ns/100ps
module tb_mp;
	reg clk, reset_n, s_wr, s0_sel;
	reg [15:0] s_addr;
	reg [31:0] s_din;
	wire interrupt_out;
	wire [63:0] s_dout;
	 
	mp MP(clk, reset_n, s_wr, s0_sel, s_addr, s_din, interrupt_out, s_dout); 
	
	parameter STEP =10;
	always #(STEP/2) clk = ~clk; //clk changes every 5 ns
	
	initial begin
	clk=0; reset_n=0; s_wr=1; s0_sel=1; s_addr = 16'h0000; s_din = 16'h0000;
	#8;	reset_n=1; s_addr = 16'h0101; s_din = 32'b0000_0111; //data[1] = 7
	#10;	s_addr = 16'h0102; s_din = 32'hffff_fff9;				  //data[2] = -7

	#10;	s_addr = 16'h0110; s_din = 16'b0000_0011_0001_0010;	//nop
	#10;	s_addr = 16'h0111; s_din = 16'b0111_0011_0011_0110;
		
	#10;	s_addr = 16'h0112; s_din = 16'b0001_0011_0001_0010;	//not A
	#10;	s_addr = 16'h0113; s_din = 16'b0111_0011_0011_0110;
		
	#10;	s_addr = 16'h0114; s_din = 16'b0010_0011_0001_0010;	//AND
	#10;	s_addr = 16'h0115; s_din = 16'b0111_0011_0011_0110;
		
	#10;	s_addr = 16'h0116; s_din = 16'b0110_0011_0001_0010;	//ADD
	#10;	s_addr = 16'h0117; s_din = 16'b0111_0011_0011_0110;
		
	#10;	s_addr = 16'h0118; s_din = 16'b1000_0011_0001_0010;	//MUL
	#10;	s_addr = 16'h0119; s_din = 16'b0111_0011_0011_0110;
	
	#10;	s_addr = 16'h0120; s_din = 1;		//start
	#5000; $stop; 
	end
endmodule