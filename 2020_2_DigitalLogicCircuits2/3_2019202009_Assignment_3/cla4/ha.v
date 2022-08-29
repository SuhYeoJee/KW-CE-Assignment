module ha(a,b,s,co); // Half adder module
	input a,b;
	output s,co;
	assign s = a^b;
	assign co=a&b;
endmodule