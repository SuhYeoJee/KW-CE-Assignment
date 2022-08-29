module cnt10(cur_cnt, clk, reset_n); //[Lab06] counter
	input clk, reset_n;
	output [3:0] cur_cnt;
	reg [3:0] cur_cnt, next_cnt;
	
	//Sequential circuit part
	always @ (posedge clk or negedge reset_n)	//async reset (active low)
	begin
		if(reset_n == 1'b0)	cur_cnt<=4'b1100;
		else						cur_cnt<=next_cnt;
	end
	
	//Combiational circuit part
	always @ (*) begin	//when cur_cnt change (clk)
		if(cur_cnt==4'b1100) next_cnt = 4'b0000;
		else if(cur_cnt==4'b0000) next_cnt = 4'b0001;
		else if(cur_cnt==4'b0001) next_cnt = 4'b0010;
		else if(cur_cnt==4'b0010) next_cnt = 4'b0011;
		else if(cur_cnt==4'b0011) next_cnt = 4'b0100;
		else if(cur_cnt==4'b0100) next_cnt = 4'b0101;
		else if(cur_cnt==4'b0101) next_cnt = 4'b0110;
		else if(cur_cnt==4'b0110) next_cnt = 4'b0111;
		else if(cur_cnt==4'b0111) next_cnt = 4'b1000;
		else if(cur_cnt==4'b1000) next_cnt = 4'b1001;
		else if(cur_cnt==4'b1001) next_cnt = 4'b1011;
		else if(cur_cnt==4'b1011) next_cnt = 4'b0000;
		else next_cnt = 4'bx;
	end
endmodule