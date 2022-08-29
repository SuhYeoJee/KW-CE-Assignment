module _dff_r_en(clk, reset_n,en,d,q);//[Lab05] resettable/ enabled d flip-flop
	input clk, reset_n, en, d;
	output reg q;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n==0)		q<=1'b0; // active low
		else if(en)			q<=d;// reset > en, write
		else					q<=q;
	end
endmodule