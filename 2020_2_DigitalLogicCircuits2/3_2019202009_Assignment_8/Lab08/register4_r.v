module register4_r(clk, reset_n, d_in, d_out); //[LAB05]Asynchronous set/resettable d ff
	input clk, reset_n; //active low
	input [3:0] d_in;
	output reg [3:0] d_out;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0)	d_out <= 3'b000;
		else					d_out <= d_in;
	end
endmodule