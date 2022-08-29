module fa(a,b,ci,s); //[Lab03] no carry cout adder
	input a, b, ci;
	output s;
	wire w0;
	
	assign w0 = a^b;
	assign s = w0^ci;
endmodule