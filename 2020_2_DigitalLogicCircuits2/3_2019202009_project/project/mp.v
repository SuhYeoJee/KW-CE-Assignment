module mp(clk, reset_n, s_wr, s0_sel, s_addr, s_din, interrupt_out, s_dout); //[project] mini processor
	input clk, reset_n, s_wr, s0_sel;
	input [15:0] s_addr;
	input [31:0] s_din;
	output interrupt_out;
	output [63:0] s_dout;
	
	reg w_opstart,mul_op_start, mul_op_clear, w_cnt_clk;
	
	wire  mul_op_done;
	wire 	w_interrupt;
	wire [3:0] cur_state, next_state, w_cnt;
	wire [15:0] cur_op, next_op,w_Addr;
	wire [31:0] cur_Ra, cur_Rb, next_Ra, next_Rb;
	wire [63:0] mul_result, alu_result, to_Rd, w_rData, w_wData;
	
	assign interrupt_out = w_interrupt;
	//assign s_dout = w_rData;
	assign s_dout = w_rData; //`test
	
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
	
	
	register4_r state_reg(.clk(clk), .reset_n(reset_n),.clear(1'b0), .d_in(next_state), .d_out(cur_state));//state register
	register32_r Ra(.clk(clk), .reset_n(reset_n), .clear(1'b0), .d_in(next_Ra), .d_out(cur_Ra));				 //Ra register
	register32_r Rb(.clk(clk), .reset_n(reset_n), .clear(1'b0), .d_in(next_Rb), .d_out(cur_Rb)); 			 //Rb register
	register16_r op(.clk(clk), .reset_n(reset_n), .clear(1'b0), .d_in(next_op), .d_out(cur_op));				 //command register
	rf rf(.clk(clk), .reset_n(reset_n), .Addr(w_Addr), .wData(w_wData), .we(w_we), .rData(w_rData)); 		 //register file
	
	mp_next_state ns(.reset_n(reset_n), .cur_state(cur_state), .next_state(next_state), //next state logic
				.op_start(w_opstart), .op_done(mul_op_done), .interrupt(w_interrupt));
	

	mp_select sel(.cur_state(cur_state), .opcode(cur_op[15:12]), .alu_result(alu_result), .mul_result(mul_result), //output logic
				.to_Rd(to_Rd), .w_we(w_we)); //`to_Rd test

	cnt10 cnt(.cur_cnt(w_cnt), .clk(w_cnt_clk), .reset_n(reset_n)); //command counter
	
	mul mul(.clk(clk), .reset_n(reset_n), .op_start(mul_op_start), .op_clear(mul_op_clear),  //multiplier
		.multiplier(cur_Ra), .multiplicand(cur_Rb), .op_done(mul_op_done), .result(mul_result)); //`delete output port
	
	alu32 alu(.a(cur_Ra),.b(cur_Rb),.op(cur_op[15:12]),.result(alu_result)); 	//alu

	mp_addr U0_mp_addr(.w_cnt(w_cnt), .s0_sel(s0_sel),.cur_state(cur_state),.s_addr(s_addr), .cur_op(cur_op), .w_Addr(w_Addr));
	mp_wData U1_data(.cur_state(cur_state), .s_din(s_din),. s_addr( s_addr), .to_Rd(to_Rd), .w_wData(w_wData));
	mp_opdata U2_opdata(.cur_state(cur_state), .w_rData(w_rData), .cur_op(cur_op), .cur_Ra(cur_Ra), .cur_Rb(cur_Rb), .next_op(next_op),.next_Ra(next_Ra), .next_Rb(next_Rb));
	
	assign w_interrupt= (w_cnt[3] & w_cnt[1]); //count 10
	always@ (*) begin
		w_cnt_clk <= 1'b0; //default
		case(cur_state)
			INIT : begin 		//init: save data
				mul_op_start <= 1'b0;
				if((s_addr[7:4]==4'h2)&&(s_addr[3:0] == 4'b0)) 
					w_opstart <= w_wData[0]; //SAVE AT CONT_REG
			end
			OP_READ	:	begin //op_READ: get command, 
				w_cnt_clk <= 1'b1; //count up
			end
			RA_READ	:	begin //RA_READ: get RA, 
				mul_op_clear <= 1'b1;
			end
			RB_READ	:	begin //RB_READ: get RB, 
				mul_op_clear <= 1'b1;
			end
			OP_WAIT2: mul_op_clear <= 1'b1;
			OP_CAL:	begin	 	//insert command at logic(MUL, ALU)
				mul_op_start <= 1'b1;
				mul_op_clear <= 1'b0;
			end			
		endcase
	end
endmodule
