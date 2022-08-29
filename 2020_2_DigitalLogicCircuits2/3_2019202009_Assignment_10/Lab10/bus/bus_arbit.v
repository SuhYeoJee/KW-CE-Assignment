module bus_arbit(clk, reset_n,m1_req, m0_req, m1_grant, m0_grant);//[Lab10]arbiter
	input clk, reset_n, m1_req, m0_req;
	output reg m1_grant, m0_grant;
	reg next_state;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0) begin //reset active low
			next_state <= 1'b0;
			m0_grant <= 1'b1;
			m1_grant <= 1'b0;
		end
		else if(next_state == 1'b0) begin // master: m0
			if(m0_req == 1'b0) begin // next master: m1
				next_state <= 1'b1;
				m0_grant <= 1'b0;
				m1_grant <= 1'b1;
			end
			else if(m0_req == 1'b1) begin //next master: m0
				next_state <= 1'b0;
				m0_grant <= 1'b1;
				m1_grant <= 1'b0;
			end
			else begin
				next_state <= 1'bx;
				m0_grant <= 1'bx;
				m1_grant <= 1'bx;
			end
		end
		else if(next_state == 1'b1) begin //master: m1
			if(m1_req == 1'b0) begin //next master: m0
				next_state <= 1'b0;
				m0_grant <= 1'b1;
				m1_grant <= 1'b0;
			end
			else if(m1_req == 1'b1) begin //next master: m1
				next_state = 1'b1;
				m0_grant <= 1'b0;
				m1_grant <= 1'b1;
			end
			else begin
				next_state <= 1'bx;
				m0_grant <= 1'bx;
				m1_grant <= 1'bx;
			end
		end
		else begin
			next_state <= 1'bx;
			m0_grant <= 1'bx;
			m1_grant <= 1'bx;
		end
	end
endmodule