module alu32(a,b,op,result); //[Lab04] 32bits arithmetic logic unit + no flags
	input [31:0] a,b;
	input [3:0] op;
	output reg [63:0] result;
	wire [31:0] w_not_a,w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;
	wire co_add, co_sub;
	
	//OPCODE ENCODING
	parameter NOP	 = 4'b0000;
	parameter NOT_A = 4'b0001;
	parameter AND	 = 4'b0010;
	parameter OR 	 = 4'b0011;
	parameter XOR 	 = 4'b0100;
	parameter XNOR  = 4'b0101;
	parameter ADD 	 = 4'b0110;
	parameter SUB 	 = 4'b0111;
	
	
	always@* begin
		case (op)
			//NOP	: result = ; //`???????
			NOT_A : result = w_not_a;
			AND	: result = w_and;
			OR		: result = w_or;
			XOR	: result = w_xor;
			XNOR	: result = w_xnor;
			ADD	: result = w_add;
			SUB	: result = w_sub;
			default: result = 32'bx;
		endcase
		result[63:32] = 32'b0; //upper 32bit
	end
	
	assign w_not_a = ~a; 	// not A
	assign w_not_b = ~b;		// not B
	assign w_and = a&b;		// a and b
	assign w_or = a|b; 		// a or b
	assign w_xor = a^b;		// a xor b
	assign w_xnor = ~(a^b);	// a xnor b
	cla32 U0_cla32(.a(a),.b(b),.ci(1'b0),.s(w_add),.co(co_add)); // add
	cla32 U1_cla32(.a(a),.b(w_not_b),.ci(1'b1),.s(w_sub),.co(co_sub)); // sub

endmodule
