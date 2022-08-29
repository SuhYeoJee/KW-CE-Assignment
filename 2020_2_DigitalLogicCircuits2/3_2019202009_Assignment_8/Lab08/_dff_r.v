module _dff_r(clk, reset_n,d,q);//[lab08] 32bits-resettable d flip-flop
	input clk, reset_n;
	input [31:0] d;
	output reg [31:0] q;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n==0)		q<=32'b0; // active low
		else					q<=d;
	end
endmodule