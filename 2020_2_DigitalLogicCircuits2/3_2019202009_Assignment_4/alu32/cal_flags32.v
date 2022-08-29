module cal_flags32(op,result,co_add,co_prev_add,co_sub,co_prev_sub,c,n,z,v); //32bits flags
	input [2:0] op;
	input [31:0] result;
	input co_add,co_prev_add,co_sub,co_prev_sub;
	output c,n,z,v;
	
	// n: MSB of result
	assign n = result[31];
	// z: result is zero 
	assign z = (result==32'b0) ? 1'b1 : 1'b0;
	// c: (op- add/sub) add/sub carry out
	assign c = (op[2:1]!=2'b11) ? 1'b0 : ((op[0]==1'b0) ? co_add : co_sub);
	// v: (op- add/sub) add/sub carry[n-1] xor carry[n-2]
	assign v = (op[2:1]!=2'b11) ? 1'b0 : ((op[0]==1'b0) ? (co_add^co_prev_add) : (co_sub^co_prev_sub));
endmodule