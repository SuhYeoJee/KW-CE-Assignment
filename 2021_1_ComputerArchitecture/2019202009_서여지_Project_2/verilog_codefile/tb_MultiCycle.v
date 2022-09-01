`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
// Company:  KWU
// Engineer: SWL
// 
// Create Date:    03/20/2021 
// Module Name:    Testbench 
// Project Name:   Multi-Cycle Processor
//
// Revision: 
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module tb_MultiCycle;

	reg tb_i_clk;
	reg tb_i_rst_n;
	wire [31:0] tb_out_pc;
	wire [7:0] tb_o_state;

	integer fp, idx;

	always #5 tb_i_clk = ~tb_i_clk;  // clock assign

	MultiCycle MC_CPU(tb_i_clk, tb_i_rst_n, tb_out_pc, tb_o_state);
	
	always @(posedge tb_i_clk) begin
		if(tb_out_pc==32'b0) begin
			fp = $fopen("mem_dump.txt","w");
			for (idx = 256; idx < 512; idx = idx + 4) begin
				$fwrite(fp,"%b ", MC_CPU.U1_MEM.mem[idx]);
				$fwrite(fp,"%b ", MC_CPU.U1_MEM.mem[idx+1]);
				$fwrite(fp,"%b ", MC_CPU.U1_MEM.mem[idx+2]);
				$fwrite(fp,"%b : ", MC_CPU.U1_MEM.mem[idx+3]);
				$fwrite(fp,"%h", MC_CPU.U1_MEM.mem[idx]);
				$fwrite(fp,"%h", MC_CPU.U1_MEM.mem[idx+1]);
				$fwrite(fp,"%h", MC_CPU.U1_MEM.mem[idx+2]);
				$fwrite(fp,"%h\n", MC_CPU.U1_MEM.mem[idx+3]);
			end
			$fclose(fp);

			fp = $fopen("reg_dump.txt","w");
			for (idx = 0; idx < 32; idx = idx + 1) begin
				$fwrite(fp,"%b ", MC_CPU.U5_RF.regs[idx][31:24]);
				$fwrite(fp,"%b ", MC_CPU.U5_RF.regs[idx][23:16]);
				$fwrite(fp,"%b ", MC_CPU.U5_RF.regs[idx][15:8]);
				$fwrite(fp,"%b : ", MC_CPU.U5_RF.regs[idx][7:0]);
				$fwrite(fp,"%h\n", MC_CPU.U5_RF.regs[idx]);
			end
			$fclose(fp);
		end
	end

	initial	begin
    $dumpfile("tb_MC.vcd");
    $dumpvars(0,MC_CPU);
  
		tb_i_clk = 1'b0;
		tb_i_rst_n = 1'b0;

		#7; 		tb_i_rst_n=1'b1;

		#1000;   // simulation wrap up here
		
		$finish;	  
	end 
endmodule 

//////////////////////////////////////////////////////////////////////////////////
