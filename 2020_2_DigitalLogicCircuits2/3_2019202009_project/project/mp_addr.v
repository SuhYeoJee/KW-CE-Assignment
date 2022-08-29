module mp_addr(w_cnt, s0_sel, cur_state, s_addr, cur_op, w_Addr);//[project] address
	input [15:0] s_addr, cur_op;
	input [3:0] w_cnt;
	input [3:0] cur_state;
	input s0_sel;
	output reg [15:0] w_Addr;
	
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
		if(s0_sel==1'b1) w_Addr[15:8] = 8'h01;//s0 select
		else w_Addr[15:8] = 8'bx;
		case(cur_state)
			INIT : w_Addr = s_addr;
			OP_READ	:	begin //op_READ: get command, 
				w_Addr[7:4] = 4'h1; //INST group
				w_Addr[3:0] = w_cnt;
			end
			RA_READ	:	begin //RA_READ: get RA, 
				w_Addr[7:4] = 4'h0;//data group
				w_Addr[3:0] = cur_op[7:4]; //Ra address
			end
			RB_READ	:	begin //RB_READ: get RB, 
				w_Addr[7:4] = 4'h0;//data group
				w_Addr[3:0] = cur_op[3:0]; //Rb address
			end
			SELECT: begin 		//select output, save at Rd
				w_Addr[7:4] = 4'h0; 		//data group
				w_Addr[4:0] = cur_op[11:8];//Rd address
			end
			RESULT :  w_Addr = 16'h0122; //interrupt register
			default : w_Addr = 16'hx;
		endcase
	end
endmodule