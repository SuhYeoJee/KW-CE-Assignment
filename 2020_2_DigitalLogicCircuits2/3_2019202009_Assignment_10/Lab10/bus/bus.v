module bus(clk, reset_n, m0_req, m0_wr, m0_address, m0_dout,
		m1_req, m1_wr, m1_address, m1_dout, s0_dout, s1_dout,
		m0_grant, m1_grant, m_din, s0_sel, s1_sel, s_address, s_wr, s_din);//[Lab10] bus
	input clk, reset_n, m0_req, m0_wr, m1_req, m1_wr;
	input [7:0] m0_address, m1_address;
	input [31:0] m0_dout, m1_dout, s0_dout, s1_dout;
	output m0_grant, m1_grant, s0_sel, s1_sel;
	output reg s_wr;
	output reg [7:0] s_address;
	output reg [31:0] m_din, s_din;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0) begin //reset
			s_wr = 1'b0;
			s_address = 8'b0;
			m_din = 32'b0;
			s_din = 32'b0;
		end
		else if((m0_grant==1'b1)&&(m1_grant==1'b0)) begin //master: m0
			s_address = m0_address;
			s_wr = m0_wr;
			if(m0_wr==1'b1) begin //write
				s_din = m0_dout;
				m_din = 32'b0;
			end
			else begin //read
				s_din = 32'b0;
				if((s0_sel==1'b1)&&(s1_sel==1'b0)) m_din=s0_dout;
				else if((s0_sel==1'b0)&&(s1_sel==1'b1)) m_din=s1_dout;
				else m_din = 32'b0;
			end
		end
		else if((m0_grant==1'b0)&&(m1_grant==1'b1)) begin //master: m1
			s_address = m1_address;
			s_wr = m1_wr;
			if(m1_wr==1'b1) begin //write
				s_din = m1_dout;
				m_din = 32'b0;
			end
			else begin //read
				s_din = 32'b0;
				if((s0_sel==1'b1)&&(s1_sel==1'b0)) m_din=s0_dout;
				else if((s0_sel==1'b0)&&(s1_sel==1'b1)) m_din=s1_dout;
				else m_din = 32'b0;
			end
		end
		else begin
			s_address = 8'bx;
			s_wr = 1'bx;
			s_din = 32'bx;
		end
	end
	
	//arbiter
	bus_arbit U0(.clk(clk), .reset_n(reset_n),.m1_req(m1_req), .m0_req(m0_req),
					.m1_grant(m1_grant), .m0_grant(m0_grant));
	//address decoder
	bus_addr U1(.s_addr(s_address), .s0_sel(s0_sel), .s1_sel(s1_sel));
endmodule