module cal_flags4(op,result,co_add,c3_add,co_sub,c3_sub,c,n,z,v); //4bits flags
	input [2:0] op;
	input [3:0] result;
	input co_add,c3_add,co_sub,c3_sub;
	output c,n,z,v;
	
	// n: MSB of result
	assign n = result[3];
	// z: result is zero 
	assign z = (result==4'b0) ? 1'b1 : 1'b0;
	// c: (op- add/sub) add/sub carry out
	assign c = (op[2:1]!=2'b11) ? 1'b0 : ((op[0]==1'b0) ? co_add : co_sub);
	// v: (op- add/sub) add/sub carry[n-1] xor carry[n-2]
	assign v = (op[2:1]!=2'b11) ? 1'b0 : ((op[0]==1'b0) ? (co_add^c3_add) : (co_sub^c3_sub));
endmodule
