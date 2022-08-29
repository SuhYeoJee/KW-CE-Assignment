`timescale 1ns/100ps
module tb_register32;
	reg[31:0] tb_d;
	reg tb_clk;
	wire[31:0] tb_q;
	
	_register32 U0_register32(.clk(tb_clk),.d(tb_d),.q(tb_q));
	
	parameter STEP =20;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 10ns
	
	initial begin
	tb_d=32'h12345678; tb_clk=0;		
	#5; tb_d=32'h98765432;
	#7; tb_d=32'hffeeddcc;
	#10; tb_d=32'hbbaa1234;
	#3; tb_d=32'h77665544;
	#10; tb_d=32'h33221100;
	#10; tb_d=32'h12345678;
	#10; $stop;
	end
endmodule