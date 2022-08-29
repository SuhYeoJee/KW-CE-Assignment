`timescale 1ns/100ps
module tb_fa;
	reg a,b;
	reg ci;
	wire s;
	
	fa fa(.a(a),.b(b),.ci(ci),.s(s));
	
	initial begin
	a = 1'b0; b = 1'b1; ci = 1'b1;
	#10; b = 4'b0;
	#10; ci = 1'b0;
	#10; a = 4'b1; b = 4'b1;
	end
endmodule