module register64_rs(clk, reset_n,set, d_init, d_in, d_out); //[LAB05]Asynchronous resettable d ff
	input clk, reset_n,set; //active low
	input [63:0] d_init, d_in;
	output reg [63:0] d_out;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0)	d_out <= 64'b0;
		else if(set == 1'b1) d_out <= d_init;
		else	d_out <= d_in;
	end
endmodule