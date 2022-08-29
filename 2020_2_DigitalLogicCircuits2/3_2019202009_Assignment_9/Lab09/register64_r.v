module register64_r(clk, reset_n,clear, d_in, d_out); //[LAB05]Asynchronous resettable d ff
	input clk, reset_n, clear; //reset active low
	input [63:0] d_in;
	output reg [63:0] d_out;
	
	always@(posedge clk or negedge reset_n)
	begin
		if((reset_n == 0))	d_out <= 64'b0;
		else if(clear == 1) d_out <= 64'b0;
		else					d_out <= d_in;
	end
endmodule