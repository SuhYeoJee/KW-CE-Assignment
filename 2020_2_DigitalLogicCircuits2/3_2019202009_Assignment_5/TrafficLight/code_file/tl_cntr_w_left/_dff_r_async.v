module _dff_r_async(clk, r, d, q); //Asynchronous set/resettable d ff
	input clk, r, d; //active low
	output q;
	reg q;
	
	always@(posedge clk or negedge r)
	begin
		if(r == 0)	q <= 1'b0;
		else					q <= d;
	end
endmodule

