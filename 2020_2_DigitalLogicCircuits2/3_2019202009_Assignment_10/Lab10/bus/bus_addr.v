module bus_addr(s_addr, s0_sel, s1_sel);//[Lab10] address decoder
	input [7:0] s_addr;
	output reg s0_sel, s1_sel;
	
	always@(s_addr)
	begin
		if(s_addr[7:5] == 3'b000) begin //slave: s0
			s0_sel = 1'b1;
			s1_sel = 1'b0;
		end
		else if(s_addr[7:5] == 3'b001) begin //slave: s1
			s0_sel = 1'b0;
			s1_sel = 1'b1;
		end
		else	 begin
			s0_sel = 1'b0;
			s1_sel = 1'b0;
		end
	end
endmodule