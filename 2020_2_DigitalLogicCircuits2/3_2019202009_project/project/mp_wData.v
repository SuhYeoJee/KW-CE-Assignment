module mp_wData(cur_state, s_din, s_addr, to_Rd, w_wData);//[project] data to write
	input [15:0] s_addr;
	input [3:0] cur_state;
	input [31:0] s_din;
	input [63:0] to_Rd;
	output reg [63:0] w_wData;
	
	//state encoding
	parameter INIT			= 4'b0000;
	parameter OP_READ		= 4'b0001;
	parameter OP_WAIT1	= 4'b0010;
	parameter RA_READ		= 4'b0011;
	parameter RB_READ 	= 4'b0100;
	parameter OP_WAIT2 	= 4'b0101;
	parameter OP_CAL		= 4'b0110;
	parameter SELECT 		= 4'b0111;
	parameter RESULT 		= 4'b1000;
	
	
	always@ (*) begin
		case(cur_state)
			INIT : begin //init: save data
				if(s_addr[7:4]==4'h0) begin		//SAVE AT DATA_REG
					w_wData[31:0] = s_din[31:0];
					w_wData[63:32] = 32'b0;
				end
				else if(s_addr[7:4]==4'h1) begin //SAVE AT INST_REG
					w_wData[15:0] = s_din[15:0];
					w_wData[63:16] = 48'b0;
				end
				else if(s_addr[7:4]==4'h2) begin	//SAVE AT CONT_REG
					w_wData[0] = s_din[0];
					w_wData[63:1] = 63'b0;
				end
				else w_wData = 64'bx; //`test
			end
			SELECT: w_wData[63:0] = to_Rd[63:0];
			RESULT : begin //result: write interrupt 1
				w_wData[0] = 1'b1;
				w_wData[63:1] = 63'b0;
			end
			default : w_wData = 64'bx; 		 //don't write
		endcase
	end
endmodule