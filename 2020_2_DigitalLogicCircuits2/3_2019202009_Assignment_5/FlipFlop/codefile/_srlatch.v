module _srlatch(r,s,q,qb); //SR Latch
	input r,s;
	output q,qb;
	
	_nor2 U0_nor2(.a(r),.b(qb),.y(q)); //use 2 2 NOR gate
	_nor2 U1_nor2(.a(q),.b(s),.y(qb));
	
endmodule