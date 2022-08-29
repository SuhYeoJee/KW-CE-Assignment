`timescale 1ns/100ps
module tb_alu32;
	reg[31:0] tb_a,tb_b;
	reg [3:0] tb_op;
	wire [63:0] tb_result;
	
	alu32 alu32(tb_a,tb_b,tb_op,tb_result);
	
	//OPCODE ENCODING
	parameter NOT_A = 4'b0000;
	parameter NOT_B = 4'b0001;
	parameter AND	 = 4'b0010;
	parameter OR 	 = 4'b0011;
	parameter XOR 	 = 4'b0100;
	parameter XNOR  = 4'b0101;
	parameter ADD 	 = 4'b0110;
	parameter SUB 	 = 4'b0111;
	
	initial begin
	tb_a=32'h0; tb_b=32'h0; tb_op= NOT_A;
	#10; tb_op= NOT_A; 	tb_a=32'h0000_FFFF;	// not A
	#10; tb_op= NOT_B; 	tb_b=32'h00FF_FF00; 	// not B
	#10; tb_op= AND;		tb_a=32'h0A0B_1100; tb_b=32'h1010_AB00; 	// and
	#10; tb_op= OR;	// or
	#10; tb_op= XOR;	// xor
	#10; tb_op= XNOR;	// xnor
	#10; tb_op= SUB;		tb_a=32'h0FFF_0000; tb_b=32'h000F_FFFF;	// sub
	#10; tb_op= ADD;	// add
	#10;
	end
endmodule
	