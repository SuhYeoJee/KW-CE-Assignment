`timescale 1ns/100ps
module tb_alu32;
	reg[31:0] tb_a,tb_b;
	reg [2:0] tb_op;
	wire [31:0] tb_result;
	wire tb_c,tb_n,tb_z,tb_v;
	
	alu32 U0_alu32(.a(tb_a),.b(tb_b),.op(tb_op),.result(tb_result),
					.c(tb_c),.n(tb_n),.z(tb_z),.v(tb_v));
	initial begin
	tb_a=32'h0; tb_b=32'h0; tb_op=3'b000; 		
	#10; tb_a=32'h0000_FFFF;	// not A
	#10; tb_b=32'h00FF_FF00; tb_op=3'b001; 	// not B
	#10; tb_a=32'h0A0B_1100; tb_b=32'h1010_AB00; tb_op=3'b010;	// and
	#10; tb_op=3'b011;	// or
	#10; tb_op=3'b100;	// xor
	#10; tb_op=3'b101;	// xnor
	#10; tb_a=32'h82C6_E581; tb_b=32'h82C6_E581; tb_op=3'b110;			// sub
	#10; tb_op=3'b111;	// add
	#10;
	end
endmodule
	