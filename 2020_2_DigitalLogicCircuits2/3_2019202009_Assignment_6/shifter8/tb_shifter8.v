`timescale 1ns/100ps
module tb_shifter8;
	reg tb_clk, tb_reset_n;
	reg [1:0] tb_shamt;
	reg [2:0] tb_op;
	reg [7:0] tb_d_in;
	wire [7:0] tb_d_out;
	wire [7:0] tb_d_next;
	
	//module instance
	shifter8 U0_shifter8(.op(tb_op),.shamt(tb_shamt),.d_in(tb_d_in),.d_out(tb_d_out),.clk(tb_clk),.reset_n(tb_reset_n));
	
	parameter STEP =10;
	always #(STEP/2) tb_clk = ~tb_clk; //clk changes every 5 ns
	
	initial begin
	tb_clk = 1; tb_reset_n=0; tb_shamt=2'b0; tb_op=3'b0; tb_d_in=8'b0;
	#13; tb_reset_n=1;
	#10; tb_op=3'b001; tb_d_in=8'b01110111;
	#20; tb_op=3'b010;
	#20; tb_shamt=2'b01;
	#30; tb_op=3'b011;
	#20; tb_op=3'b010; tb_shamt=2'b11;
	#10; tb_op=3'b001; tb_d_in=8'b10000111;
	#30; tb_op=3'b100; tb_shamt=2'b01;
	#30; tb_shamt=2'b11;
	#20; tb_reset_n=0;
	#10; $stop;
	end
endmodule