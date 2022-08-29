`timescale 1ns/100ps
module tb_clb4;
	reg [3:0] a,b;
	reg ci;
	wire c1, c2, c3,co;
	
	clb4 clb4(a,b,ci,c1,c2,c3,co);
	
	initial begin
	a = 4'b0000; b = 4'b0000; ci = 1'b1;
	#10; b = 4'b1111;
	#10; ci = 1'b0;
	#10; a = 4'b1100;
	end
endmodule