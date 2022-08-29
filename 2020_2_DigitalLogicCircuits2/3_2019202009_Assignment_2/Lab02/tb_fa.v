`timescale 1ns/100ps

module tb_fa;
	reg a, b, ci;
	wire s, co;
	
	fa fa(.a(a),.b(b),.ci(ci),.s(s),.co(co)); // Full adder
	
	initial
	begin
	a=0; b=0; ci=0; //exhaustive verification
   #10; ci=1;
   #10; b=1;
   #10; ci=0;
   #10; a=1;
	#10; ci=1;
	#10; b=0;
	#10; ci=0;
	#10;
   end
endmodule
