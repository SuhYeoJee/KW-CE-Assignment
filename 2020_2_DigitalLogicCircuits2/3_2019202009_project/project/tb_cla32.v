`timescale 1ns/100ps
module tb_cla32;
	reg [31:0] a,b;
	reg ci;
	wire [31:0] s;
	wire co;

	cla32 cla32(a,b,ci,s,co);
	
	initial begin
	a = 32'h0000_0000; b = 32'hefff_ffff; ci = 1'b1;
	#10; b = 32'hffff_ffff;
	#10; ci = 1'b0;
	#10; a = 32'h1234_1234; b = 32'haaaa_aaaa;
	end
endmodule