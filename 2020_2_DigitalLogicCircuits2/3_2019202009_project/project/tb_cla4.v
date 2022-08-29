`timescale 1ns/100ps
module tb_cla4;
	reg [3:0] a,b;
	reg ci;
	wire [3:0] s;
	wire co;

	cla4 cla4(a,b,ci,s,co);
	
	initial begin
	a = 4'b0011; b = 4'b0000; ci = 1'b1;
	#10; b = 4'b1111;
	#10; ci = 1'b0;
	#10; a = 4'b1100;
	end
endmodule