module _NAND(a,b,y); //my NAND module
	input a, b;
	output y;
	assign y = ~(a&b);
endmodule

module INV(a,y); //my Inverter module
	input a;
	output y;
	assign y = ~a;
endmodule

module mx2(y, d0, d1, s); // 2 to 1 MUX module
	input d0, d1, s;
	output y;
	wire sb, w0, w1;
	
	INV iv0(.a(s), .y(sb)); // NOT 's' for nd20
	_NAND nd20(.a(d0),.b(sb),.y(w0)); // 3 NAND GATE 
	_NAND nd21(.a(d1),.b(s),.y(w1));
	_NAND nd22(.a(w0),.b(w1),.y(y));
	
endmodule