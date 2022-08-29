module bus(clk, reset_n, m_req, m_wr, m_addr, m_dout, s_dout,
				m_grant, m_din, s_addr, s_wr, s_din, s_sel);//[Lab10] bus
	input clk, reset_n, m_req, m_wr;
	input [15:0] m_addr; // 0x0100 ~ 0x1ff
	input [31:0] m_dout;
	input [63:0] s_dout;
	output s_sel, m_grant;
	output reg s_wr;
	output reg [15:0] s_addr;
	output reg [63:0] m_din, s_din;
	
	always@(posedge clk or negedge reset_n) begin
		if(reset_n == 1'b0) begin //reset
			s_addr = 16'b0;
			s_wr = 1'b0;
			m_din = 64'b0;
			s_din = 64'b0;
		end
		else if(m_grant==1'b1) begin //master: m
			s_addr = m_addr;
			s_wr = m_wr;
			if(m_wr==1'b1) begin //write
				s_din[31:0] = m_dout;
				s_din[63:32] = 32'b0;
				m_din = 64'b0;
			end
			else begin 				//read
				s_din = 64'b0;
				if(s_sel==1'b1) m_din=s_dout;
				else m_din=64'bx; //address error
			end
		end
		else begin //master not granted
			s_addr = 16'bx;
			s_wr = 1'bx;
			s_din = 64'bx;
		end
	end
	
	assign m_grant = m_req; //arbiter (1 master)
	
	assign s_sel = ( s_addr[15:8] == 8'h01 )?1'b1:1'b0; //address decoder
	
	
endmodule