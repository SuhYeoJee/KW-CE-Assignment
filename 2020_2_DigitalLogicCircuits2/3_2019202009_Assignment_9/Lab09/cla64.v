module cla64(a,b,ci,s,co); //[Lab09]32bits CLA
	input [63:0] a,b;	//a+b+ci = s, co
	input ci;
	output [63:0] s;
	output co;
	wire c1;
	
	//instance of cla32
	cla32 U0_cla32(.a(a[31:0]),.b(b[31:0]),.ci(ci),.s(s[31:0]),.co(c1));
	cla32 U1_cla32(.a(a[63:32]),.b(b[63:32]),.ci(c1),.s(s[63:32]),.co(co));
endmodule