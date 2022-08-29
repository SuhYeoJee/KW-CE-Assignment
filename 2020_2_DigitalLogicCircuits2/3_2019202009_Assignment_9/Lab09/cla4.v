module cla4(a,b,ci,s,co); //[Lab03] Carry Look-ahead Adder
	input [3:0] a,b;
	input ci;
	output [3:0] s;
	output co;
	wire c1,c2,c3;
	
	clb4 U0_clb4(.a(a),.b(b),.ci(ci),.c1(c1),.c2(c2),.c3(c3),.co(co)); // get carry
	fa_v2 U1_fa_v2(.a(a[0]),.b(b[0]),.ci(ci),.s(s[0])); //get s
	fa_v2 U2_fa_v2(.a(a[1]),.b(b[1]),.ci(c1),.s(s[1]));
	fa_v2 U3_fa_v2(.a(a[2]),.b(b[2]),.ci(c2),.s(s[2]));
	fa_v2 U4_fa_v2(.a(a[3]),.b(b[3]),.ci(c3),.s(s[3]));
endmodule
	