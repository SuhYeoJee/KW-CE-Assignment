module alu32(a,b,op,result,c,n,z,v); //32bits arithmetic logic unit 
	input [31:0] a,b;
	input [2:0] op;
	output [31:0] result;
	output c,n,z,v;
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;
	wire c0_prev_add, co_add, co_prev_sub, co_sub;
	
	_inv_32bits U0_inv_32bits(.a(a),.y(w_not_a)); // Not A
	_inv_32bits U1_inv_32bits(.a(b),.y(w_not_b)); // Not B
	_and2_32bits U2_and2_32bits(.a(a),.b(b),.y(w_and)); // And
	_or2_32bits U3_or2_32bits(.a(a),.b(b),.y(w_or)); // Or
	_xor2_32bits U4_xor2_32bits(.a(a),.b(b),.y(w_xor)); // xor
	_xnor2_32bits U5_xnor2_32bits(.a(a),.b(b),.y(w_xnor)); // xnor
	cla32 U6_cla32(.a(a),.b(b),.ci(0),.s(w_add),.co(co_add),.co_prev(co_prev_add)); // add
	cla32 U7_cla32(.a(a),.b(w_not_b),.ci(1),.s(w_sub),.co(co_sub),.co_prev(co_prev_sub)); // sub
	
	// select 1 operation
	mx8_32bits U8_mx8_32bits(.a(w_not_a), .b(w_not_b), .c(w_and), .d(w_or), .e(w_xor), .f(w_xnor),
					.g(w_add), .h(w_sub), .s0(op[0]),.s1(op[1]),.s2(op[2]), .y(result));
	
	// calculate flags
	cal_flags32 U9_cal_flags32(.op(op),.result(result),.co_add(co_add),.co_prev_add(co_prev_add),
					.co_sub(co_sub),.co_prev_sub(co_prev_sub),.c(c),.n(n),.z(z),.v(v));
endmodule
