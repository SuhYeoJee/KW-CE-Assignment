`timescale 1ns/100ps

module tb_cla4;
	reg [3:0] tb_a, tb_b;
	reg tb_ci;
	wire [3:0] tb_s;
	wire tb_co;
	wire [4:0] tb_result;

	assign tb_result = {tb_co, tb_s};	
	cla4 U0_cla4(.a(tb_a),.b(tb_b),.ci(tb_ci),.s(tb_s),.co(tb_co));
	
	initial begin
	tb_a=0;tb_b=0; tb_ci=0;
   #10; tb_a=4'b0101;tb_b=4'b0010; 			// 5+2=7			no carry
   #10; tb_b=4'b0011; 							// 5+3=8			fa00, fa01, fa02 carry
	#10; tb_a=4'b1101; 							// -3+3=0			carry out
	#10; tb_a=4'b0100;tb_b=4'b0010;tb_ci=1;// 4+2+1=7			no carry
	#10; tb_b=4'b0101; 							// 4+5+1=10			fa00,fa02 carry
	#10; tb_a=4'b1010; 							// -6+5+1=0			carry out
	#10;
   end
endmodule
