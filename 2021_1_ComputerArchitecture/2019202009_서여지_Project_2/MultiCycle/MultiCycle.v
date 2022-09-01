`timescale 1ns / 1ps
module MultiCycle(i_clk, i_rst_n, o_pc, o_state,u5yutvmxoo,w_lo_reg); 
input i_clk, i_rst_n;output wire [7:0] o_state;output reg [31:0] o_pc; output wire [31:0] u5yutvmxoo,w_lo_reg; wire yoitvaz3gp, 
z4q358reos, qwgk629tip, zxzhds3a7l, b2xru3h7wz, u4f3u4or46;wire [1:0] ixke9z3d9d;wire [2:0] zdryj6f7n4;
wire [1:0] ggeryasmb2, z4f46old35; wire [2:0] kokdmekj8x, sb3v1cibp6;wire [4:0] w3mn01lk0c;wire [3:0] ji45qb7sj8;
wire [2:0] n6nsq5nkqa; wire [4:0] kpbtkrl7ck; wire [31:0] mu0mbnaio1;wire [31:0] h62n60w1b6, rsm5meh0ah, gav2slx1zn, 
w560j0iust, ni9dqtahl2; wire [31:0] qmfqns1wjz, fku4icns63, ystp5dx6f9, gqtyldqrh8, q6cpd7uw8d;
wire [31:0] jx7bq3fo2i, gs58vxdzkm, fy051e8tr2, bsnckksks3; wire [9:0] daf4pxb5bp; wire xhbioqh67a, e5x4ua0v7v, 
xj43snd9nw, g13zd367es, ol5i9nfvlx, bo0iohlrhl; wire [31:0] wxcz26w67r,xdcklojvqg; wire [4:0] kr1je6ufns;
wire [31:0] w_hi_reg; assign o_state = daf4pxb5bp[7:0]; assign mu0mbnaio1 = {h62n60w1b6[31:28], ni9dqtahl2[25:0], 
2'b00}; always @(posedge i_clk or negedge i_rst_n) begin if (i_rst_n==1'b0) o_pc <= 32'b0; else begin if (daf4pxb5bp[9:8]==
2'b0) begin if (bo0iohlrhl==1'b1) o_pc <= rsm5meh0ah; else o_pc <= h62n60w1b6; end end end assign ol5i9nfvlx = (n6nsq5nkqa==3'b000) 
? 1'b1 : (n6nsq5nkqa==3'b100) ? xhbioqh67a : (n6nsq5nkqa==3'b101) ? ~xhbioqh67a : (n6nsq5nkqa==3'b110) ? ~g13zd367es :
(n6nsq5nkqa==3'b111) ? g13zd367es : 1'b1; assign bo0iohlrhl = b2xru3h7wz & ol5i9nfvlx; assign rsm5meh0ah = (ggeryasmb2==2'b00) ? 
u5yutvmxoo : (ggeryasmb2==2'b01) ? q6cpd7uw8d : (ggeryasmb2==2'b10) ? mu0mbnaio1 : (ggeryasmb2==2'b11) ? h62n60w1b6 : 32'bx;
RFF U0_PC (i_clk, i_rst_n, rsm5meh0ah, bo0iohlrhl, h62n60w1b6); assign gav2slx1zn = (yoitvaz3gp==1'b0) ? h62n60w1b6 : q6cpd7uw8d;
MEM U1_MEM(i_clk, zxzhds3a7l, ixke9z3d9d, gav2slx1zn, fy051e8tr2, w560j0iust); EFF U2_IR (i_clk, w560j0iust, z4q358reos, 
ni9dqtahl2); DFF U3_MDR(i_clk, w560j0iust, bsnckksks3); MainFSM U4_FSM(i_clk, i_rst_n, ni9dqtahl2[31:26], ni9dqtahl2[5:0], 
n6nsq5nkqa, b2xru3h7wz, yoitvaz3gp, zxzhds3a7l, ixke9z3d9d, zdryj6f7n4, z4q358reos, u4f3u4or46, ggeryasmb2, w3mn01lk0c, ji45qb7sj8, 
kokdmekj8x, sb3v1cibp6, qwgk629tip, z4f46old35, daf4pxb5bp); assign kpbtkrl7ck = (z4f46old35==2'b00) ? ni9dqtahl2[20:16] :
(z4f46old35==2'b01) ? ni9dqtahl2[15:11] : (z4f46old35==2'b10) ? 5'd31 : (z4f46old35==2'b11) ? ni9dqtahl2[25:21] : 5'bx; assign jx7bq3fo2i = (zdryj6f7n4==3'b000) ? 
q6cpd7uw8d : (zdryj6f7n4==3'b001) ? bsnckksks3 : (zdryj6f7n4==3'b010) ? w_lo_reg :(zdryj6f7n4==3'b011) ? w_hi_reg :
(zdryj6f7n4==3'b100) ? h62n60w1b6 : 32'bx;RF U5_RF(i_clk,i_rst_n,ni9dqtahl2[25:21],ni9dqtahl2[20:16],kpbtkrl7ck,jx7bq3fo2i,
qwgk629tip,wxcz26w67r,xdcklojvqg); DFF U6_A (i_clk,wxcz26w67r,gs58vxdzkm); DFF U7_B (i_clk,xdcklojvqg,fy051e8tr2);
SEU U8_SEU(ni9dqtahl2[15:0], qmfqns1wjz, u4f3u4or46); assign kr1je6ufns = ni9dqtahl2[10:6]; assign fku4icns63 = (kokdmekj8x==
3'b000) ? gs58vxdzkm : (kokdmekj8x==3'b001) ? 32'd4 : (kokdmekj8x==3'b010) ? 32'd0 : (kokdmekj8x==3'b011) ? h62n60w1b6 :
(kokdmekj8x==3'b100) ? fy051e8tr2 : 32'bx; assign ystp5dx6f9 = (sb3v1cibp6==3'b000) ? fy051e8tr2 : (sb3v1cibp6==3'b001) ? 32'd4 :
(sb3v1cibp6==3'b010) ? 32'd0 : (sb3v1cibp6==3'b011) ? qmfqns1wjz : (sb3v1cibp6==3'b100) ? qmfqns1wjz<<2 : 32'bx;
ALU U9_ALU (fku4icns63, ystp5dx6f9, kr1je6ufns, w3mn01lk0c, ji45qb7sj8, u5yutvmxoo, xhbioqh67a, e5x4ua0v7v, xj43snd9nw, 
g13zd367es); MULT U10_MUL (i_clk, i_rst_n, fku4icns63, ystp5dx6f9, w3mn01lk0c, w_hi_reg, w_lo_reg); assign gqtyldqrh8 = 
(w3mn01lk0c==5'b01000) ? q6cpd7uw8d : u5yutvmxoo; DFF U11_ALUO(i_clk, gqtyldqrh8, q6cpd7uw8d); endmodule
module DFF(fku4icns63,ni9dqtahl2, qmfqns1wjz); input [31:0] ni9dqtahl2;input fku4icns63;output reg[31:0] qmfqns1wjz;
always@(posedge fku4icns63) begin qmfqns1wjz <= ni9dqtahl2; end endmodule module EFF(fku4icns63,ni9dqtahl2, w560j0iust, 
qmfqns1wjz); input [31:0] ni9dqtahl2; input fku4icns63, w560j0iust; output reg[31:0] qmfqns1wjz; always@(posedge fku4icns63) 
begin if (w560j0iust==1'b1) qmfqns1wjz <= ni9dqtahl2; else qmfqns1wjz <= qmfqns1wjz; end endmodule
module RFF(fku4icns63,gav2slx1zn,ni9dqtahl2, w560j0iust, qmfqns1wjz); input [31:0] ni9dqtahl2;
input fku4icns63, gav2slx1zn, w560j0iust; output reg[31:0] qmfqns1wjz; always@(posedge fku4icns63 or negedge gav2slx1zn) begin
if (gav2slx1zn==1'b0) begin qmfqns1wjz <= 32'b0; end else begin if (w560j0iust==1'b1) qmfqns1wjz <= ni9dqtahl2;
else qmfqns1wjz <= qmfqns1wjz; end end endmodule
module ALU(i_data1, i_data2, shamt, ALUop, ALUctrl, o_result, o_zero, o_overflow, o_carry, o_positive);
input [31:0] i_data1, i_data2; input [4:0] shamt; input [4:0] ALUop; input [3:0] ALUctrl;
output  [31:0] o_result; output  o_overflow, o_carry; output o_zero, o_positive;
wire [31:0] ofjqn29td7, mj6fupar7g; wire [4:0] kr1je6ufns; wire [4:0] xdcklojvqg;
wire [3:0] wxcz26w67r; reg [31:0] bo0iohlrhl; reg  ol5i9nfvlx, g13zd367es;
wire xj43snd9nw, e5x4ua0v7v; assign ofjqn29td7 = i_data1; assign xdcklojvqg = ALUop;
assign wxcz26w67r = ALUctrl; assign o_result = bo0iohlrhl; assign o_zero = xj43snd9nw;
assign o_positive = e5x4ua0v7v; reg [31:0] xhbioqh67a; wire [4:0] daf4pxb5bp;
wire [31:0] bsnckksks3, fy051e8tr2; assign daf4pxb5bp = (wxcz26w67r[0]==1'b0) ? kr1je6ufns : ofjqn29td7[4:0];
assign bsnckksks3 = (wxcz26w67r[1]==1'b0) ? ofjqn29td7 : mj6fupar7g; assign fy051e8tr2 = 
(wxcz26w67r[1]==1'b0) ? mj6fupar7g : ofjqn29td7; assign mj6fupar7g = i_data2; assign kr1je6ufns = shamt;
assign xj43snd9nw = (bo0iohlrhl == 32'b0) ? 1'b1 : 1'b0; assign e5x4ua0v7v = ((bo0iohlrhl[31]==1'b0)
&&(xj43snd9nw==1'b0)) ? 1'b1 : 1'b0; always @(*) begin case (xdcklojvqg) 5'b00000 : begin
bo0iohlrhl = bsnckksks3 & fy051e8tr2; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b00001 : begin
bo0iohlrhl = bsnckksks3 | fy051e8tr2; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b00010 : begin
bo0iohlrhl = ~(bsnckksks3 | fy051e8tr2); g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b00011 : begin
bo0iohlrhl = bsnckksks3 ^ fy051e8tr2; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b00100 : begin
{g13zd367es, bo0iohlrhl} = $signed(bsnckksks3) + $signed(fy051e8tr2); ol5i9nfvlx = (bsnckksks3[31]
&fy051e8tr2[31]&~bo0iohlrhl[31])|(~bsnckksks3[31]&~fy051e8tr2[31]&bo0iohlrhl[31]); end
5'b00101 : begin {g13zd367es, bo0iohlrhl} = $unsigned(bsnckksks3) + $unsigned(fy051e8tr2);
ol5i9nfvlx = g13zd367es; end 5'b00110 : begin xhbioqh67a = ~(fy051e8tr2); {g13zd367es, bo0iohlrhl}
= $signed(bsnckksks3) + $signed(xhbioqh67a) + 1; ol5i9nfvlx = (bsnckksks3[31]&xhbioqh67a[31]&~bo0iohlrhl[31])
|(~bsnckksks3[31]&~xhbioqh67a[31]&bo0iohlrhl[31]); end 5'b00111 : begin {g13zd367es, bo0iohlrhl} = 
$unsigned(bsnckksks3) - $unsigned(fy051e8tr2); ol5i9nfvlx = g13zd367es; end 5'b01000 : begin
bo0iohlrhl = 32'h0; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b01101 : begin bo0iohlrhl = fy051e8tr2 << daf4pxb5bp;
g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b01110 : begin bo0iohlrhl = fy051e8tr2 >> daf4pxb5bp;
g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b01111 : begin bo0iohlrhl = $signed(fy051e8tr2) >>> daf4pxb5bp;
g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b10000 : begin bo0iohlrhl = ($signed(bsnckksks3) < 
$signed(fy051e8tr2)) ? 32'b1 : 32'b0; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end 5'b10001 : begin
bo0iohlrhl = ($unsigned(bsnckksks3) < $unsigned(fy051e8tr2)) ? 32'b1 : 32'b0; g13zd367es = 1'b0;
ol5i9nfvlx = 1'b0; end 5'b11101 : begin g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; bo0iohlrhl = {fy051e8tr2[15:0], 
bsnckksks3[15:0]}; end 5'b11110 : begin g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; bo0iohlrhl = {bsnckksks3[31:16], 
fy051e8tr2[15:0]}; end 5'b11111 : begin g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; bo0iohlrhl = {fy051e8tr2[15:0], 16'b0};
end default   : begin bo0iohlrhl = 32'h0; g13zd367es = 1'b0; ol5i9nfvlx = 1'b0; end
endcase end assign o_overflow = ol5i9nfvlx; assign o_carry = g13zd367es; endmodule

module MULT(i_clk,i_rst_n,i_data1, i_data2, ALUop, o_hi, o_lo);
input i_clk,i_rst_n; input [31:0] i_data1, i_data2; input [4:0] ALUop; output [31:0] o_hi, o_lo;
reg [31:0] xdcklojvqg, wxcz26w67r; wire [31:0] bo0iohlrhl, ol5i9nfvlx; wire g13zd367es, xj43snd9nw;
wire [4:0] e5x4ua0v7v; reg [31:0] xhbioqh67a, daf4pxb5bp; assign bo0iohlrhl = i_data1;
assign o_lo = daf4pxb5bp; always @(posedge g13zd367es or negedge xj43snd9nw) begin if(!xj43snd9nw) begin
xhbioqh67a <= 32'b0; daf4pxb5bp <= 32'b0; end else begin if (e5x4ua0v7v == 5'b10010) begin
xhbioqh67a <= $unsigned(bo0iohlrhl); daf4pxb5bp <= wxcz26w67r; end else if (e5x4ua0v7v == 5'b10011) begin
xhbioqh67a <= xdcklojvqg; daf4pxb5bp <= $unsigned(bo0iohlrhl); end else begin xhbioqh67a <= xdcklojvqg;
daf4pxb5bp <= wxcz26w67r; end end end assign ol5i9nfvlx = i_data2; assign g13zd367es = i_clk;
assign xj43snd9nw = i_rst_n; always @( * ) begin if (e5x4ua0v7v == 5'b01001) begin {xdcklojvqg, wxcz26w67r} = 
$signed(bo0iohlrhl) * $signed(ol5i9nfvlx); end else if (e5x4ua0v7v == 5'b01010) begin
{xdcklojvqg, wxcz26w67r} = $unsigned(bo0iohlrhl) * $unsigned(ol5i9nfvlx); end else if (e5x4ua0v7v == 
5'b01011) begin wxcz26w67r = $signed(bo0iohlrhl) / $signed(ol5i9nfvlx); xdcklojvqg = $signed(bo0iohlrhl) % 
$signed(ol5i9nfvlx); end else if (e5x4ua0v7v == 5'b01100) begin wxcz26w67r = $unsigned(bo0iohlrhl) / 
$unsigned(ol5i9nfvlx); xdcklojvqg = $unsigned(bo0iohlrhl) % $unsigned(ol5i9nfvlx); end
else if (e5x4ua0v7v == 5'b10010) begin xdcklojvqg = $unsigned(bo0iohlrhl); wxcz26w67r = daf4pxb5bp;
end else if (e5x4ua0v7v == 5'b10011) begin xdcklojvqg = xhbioqh67a; wxcz26w67r = $unsigned(bo0iohlrhl);
end else begin wxcz26w67r = daf4pxb5bp; xdcklojvqg = xhbioqh67a; end end assign e5x4ua0v7v = ALUop;
assign o_hi = xhbioqh67a;endmodule 
module SEU(ofjqn29td7,mj6fupar7g,kr1je6ufns);
input [15:0] ofjqn29td7; input kr1je6ufns; output [31:0] mj6fupar7g; reg [31:0] mj6fupar7g;
always@(*) begin if (kr1je6ufns==1'b0) begin mj6fupar7g = {16'h0000, ofjqn29td7[15:0]};
end else begin if(ofjqn29td7[15]==1'b1) begin mj6fupar7g = {16'hFFFF, ofjqn29td7[15:0]};
end else begin mj6fupar7g = {16'h0000, ofjqn29td7[15:0]}; end end end endmodule
module MainFSM(ojmen5xq5s, ivgyfpmz0h, wxcz26w67r, bo0iohlrhl, ol5i9nfvlx, g13zd367es,
xj43snd9nw, e5x4ua0v7v, xhbioqh67a, daf4pxb5bp, bsnckksks3,xdcklojvqg, kr1je6ufns, 
mj6fupar7g,fy051e8tr2, ofjqn29td7, gs58vxdzkm, jx7bq3fo2i, q6cpd7uw8d, gqtyldqrh8);
input ojmen5xq5s, ivgyfpmz0h;input [5:0] wxcz26w67r, bo0iohlrhl;output [2:0] ol5i9nfvlx;
output g13zd367es, xj43snd9nw, e5x4ua0v7v, bsnckksks3, jx7bq3fo2i, xdcklojvqg;
output [1:0] kr1je6ufns, q6cpd7uw8d, xhbioqh67a;output [2:0] ofjqn29td7, gs58vxdzkm;
output [2:0] daf4pxb5bp;output [4:0] mj6fupar7g;output [3:0] fy051e8tr2;output [9:0] gqtyldqrh8;
wire [1:0] u5yutvmxoo;reg [7:0] ystp5dx6f9, fku4icns63;reg [7:0] qmfqns1wjz;reg [7:0] ni9dqtahl2;
reg [39:0] w560j0iust[0:255];wire [39:0] gav2slx1zn;wire [4:0] rsm5meh0ah;wire h62n60w1b6;
wire [7:0] mu0mbnaio1, n6nsq5nkqa, ji45qb7sj8, w3mn01lk0c;initial begin
$readmemb("MICRO_ROM.txt", w560j0iust, 0, 127); w560j0iust[8'h80]={10'bx0xx0xxxxx, 
10'b0000001100, 10'b0010000xxx, 10'bxx011xxxxx};w560j0iust[8'h81]={10'bx0xx000000, 
10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx};w560j0iust[8'h82]={10'bx0xx0xxxxx, 10'b0x00000000, 
10'b1000000xxx, 10'bxx011xxxxx};w560j0iust[8'h83]={10'bx0xx001000, 10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 
10'bxx000xxxxx};w560j0iust[8'h84]={10'bx0xx0xxxxx, 10'b0x00000000, 10'b1100000xxx, 10'bxx011xxxxx};
w560j0iust[8'h85]={10'bx0xx001000, 10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx}; w560j0iust[8'h86]=
{10'bx0xx0xxxxx, 10'b0100001100, 10'b1000000xxx, 10'bxx010xxxxx};w560j0iust[8'h87]={10'b10000xxxxx, 
10'b0xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx011xxxxx};w560j0iust[8'h88]={10'bx0xx000001, 10'b1xxxxxxxxx, 
10'bxxxxxxxxxx, 10'bxx000xxxxx};w560j0iust[8'h89]={10'bxxxxxxxxxx, 10'bxxxxxxxxxx, 10'bxxxxxxxxxx, 
10'bxxxxxxxxxx};w560j0iust[8'h8a]={10'b11000xxxxx, 10'b0xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx};
w560j0iust[8'h8b]={10'bx0xx0xxxxx, 10'b0xxxxxxxxx, 10'bxxxxxxx000, 10'b10100xxxxx};w560j0iust[8'h8c]=
{10'bx0xx0xxxxx, 10'b0000001111, 10'b1110000xxx, 10'bxx011xxxxx};w560j0iust[8'h8d]={10'bx0xx000000, 
10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx};w560j0iust[8'h8e]={10'bx0xx0xxxxx, 10'b0010001111, 
10'b1010000xxx, 10'bxx011xxxxx};w560j0iust[8'h8f]={10'bx0xx000000, 10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 
10'bxx000xxxxx};w560j0iust[8'h90]={10'bx0xx0xxxxx, 10'b0010001111, 10'b1100000xxx, 10'bxx011xxxxx};
w560j0iust[8'h91]={10'bx0xx000000, 10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx};w560j0iust[8'h92]=
{10'bx0xx0xxxxx, 10'b0x01000001, 10'b1010000xxx, 10'bxx011xxxxx};w560j0iust[8'h93]={10'bx0xx001000, 
10'b1xxxxxxxxx, 10'bxxxxxxxxxx, 10'bxx000xxxxx};end assign gqtyldqrh8 = {u5yutvmxoo, ystp5dx6f9};
My_State_ROM U0_MyROM (wxcz26w67r, bo0iohlrhl, n6nsq5nkqa); Main_ROM U1_MNROM (wxcz26w67r, bo0iohlrhl, 
ji45qb7sj8, h62n60w1b6); Jump_ROM U2_JPROM (wxcz26w67r, bo0iohlrhl, w3mn01lk0c); assign mu0mbnaio1 = 
h62n60w1b6 ? n6nsq5nkqa : ji45qb7sj8;always @(posedge ojmen5xq5s or negedge ivgyfpmz0h) begin
if (ivgyfpmz0h == 1'b0) begin ystp5dx6f9 <= 8'b0;end else begin if (u5yutvmxoo==2'b00) ystp5dx6f9 <= 8'b0;
else if (u5yutvmxoo==2'b01) ystp5dx6f9 <= mu0mbnaio1; else if (u5yutvmxoo==2'b10) ystp5dx6f9 <= w3mn01lk0c;
else if (u5yutvmxoo==2'b11) ystp5dx6f9 <= ystp5dx6f9 + 1;else ystp5dx6f9 <= 8'bx; end end assign gav2slx1zn = 
w560j0iust[ystp5dx6f9];assign xj43snd9nw = gav2slx1zn[39];assign e5x4ua0v7v = gav2slx1zn[38];
assign xhbioqh67a = gav2slx1zn[37:36];assign bsnckksks3 = gav2slx1zn[35];assign q6cpd7uw8d = gav2slx1zn[34:33];
assign daf4pxb5bp = gav2slx1zn[32:30];assign jx7bq3fo2i = gav2slx1zn[29];assign xdcklojvqg = gav2slx1zn[28];
assign ofjqn29td7 = gav2slx1zn[27:25];assign gs58vxdzkm = gav2slx1zn[24:22];assign mj6fupar7g = gav2slx1zn[21:17];
assign fy051e8tr2 = gav2slx1zn[16:13];assign ol5i9nfvlx = gav2slx1zn[12:10];assign kr1je6ufns = gav2slx1zn[9:8];
assign g13zd367es = gav2slx1zn[7];assign u5yutvmxoo = gav2slx1zn[6:5];assign rsm5meh0ah = gav2slx1zn[4:0];endmodule
module Main_ROM (kr1je6ufns, ol5i9nfvlx, e5x4ua0v7v, jx7bq3fo2i);
input [5:0] kr1je6ufns, ol5i9nfvlx;output reg [7:0] e5x4ua0v7v;output reg jx7bq3fo2i;always @(*) begin
if (kr1je6ufns==6'b000000) begin if (ol5i9nfvlx==6'b100000) begin e5x4ua0v7v = 8'b10000010;
jx7bq3fo2i = 1'b0; end else if (ol5i9nfvlx==6'b100010) begin e5x4ua0v7v = 8'b10000100;
jx7bq3fo2i = 1'b0; end else if (ol5i9nfvlx==6'b000000) begin e5x4ua0v7v = 8'b10010010; jx7bq3fo2i = 1'b0;
end else begin e5x4ua0v7v = 8'bxxxxxxxx; jx7bq3fo2i = 1'b1;end end else if (kr1je6ufns==6'b001101) begin
e5x4ua0v7v = 8'b10000000; jx7bq3fo2i = 1'b0; end else if (kr1je6ufns==6'b100011) begin
e5x4ua0v7v = 8'b10000110; jx7bq3fo2i = 1'b0; end else if (kr1je6ufns==6'b101011) begin e5x4ua0v7v = 8'b10000110;
jx7bq3fo2i = 1'b0; end else if (kr1je6ufns==6'b000010) begin e5x4ua0v7v = 8'b10001011; jx7bq3fo2i = 1'b0; end
else if (kr1je6ufns==6'b001111) begin e5x4ua0v7v = 8'b10001100; jx7bq3fo2i = 1'b0; end else if (kr1je6ufns==6'b011001) begin
e5x4ua0v7v = 8'b10001110; jx7bq3fo2i = 1'b0; end else if (kr1je6ufns==6'b011000) begin e5x4ua0v7v = 8'b10010000;
jx7bq3fo2i = 1'b0; end else begin e5x4ua0v7v = 8'bxxxxxxxx; jx7bq3fo2i = 1'b1;end end endmodule
module Jump_ROM (b2xru3h7wz, kr1je6ufns, ol5i9nfvlx);
input [5:0] b2xru3h7wz, kr1je6ufns; output reg [7:0] ol5i9nfvlx; always @(*) begin if (b2xru3h7wz==6'b000000) begin
if (kr1je6ufns==6'bxxxxxx) begin ol5i9nfvlx = 8'bxxxxxxxx; end else begin ol5i9nfvlx = 8'bxxxxxxxx; end end
else if (b2xru3h7wz==6'b100011) begin ol5i9nfvlx = 8'b10000111; end else if (b2xru3h7wz==6'b101011) begin
ol5i9nfvlx = 8'b10001010; end else begin ol5i9nfvlx = 8'bxxxxxxxx; end end endmodule
module MEM(i_clk, MemWrite, DatWidth, i_addr, i_data, o_data);
input i_clk, MemWrite;input [1:0] DatWidth;input [31:0] i_addr;input [31:0] i_data;output [31:0] o_data;
reg [7:0] mem[0:2047];reg [31:0] ofjqn29td7;wire [31:0] mj6fupar7g;wire [31:0] kr1je6ufns;
wire xdcklojvqg, wxcz26w67r;wire [1:0] bo0iohlrhl;wire [31:0] ol5i9nfvlx;reg t_we;reg [31:0] t_addr, t_data;
assign o_data = ofjqn29td7;assign kr1je6ufns = i_addr;assign ol5i9nfvlx = i_data;
assign mj6fupar7g = {kr1je6ufns[31:02], kr1je6ufns[01:00] & bo0iohlrhl} & 32'h000007FF;
assign xdcklojvqg = i_clk;assign wxcz26w67r = MemWrite;assign bo0iohlrhl = DatWidth;initial begin
$readmemb("MAIN_RAM.txt", mem, 0, 511);t_we = 1'b0;end always @(posedge xdcklojvqg or posedge t_we) begin
if (t_we==1'b0) begin if(wxcz26w67r==1'b1) begin if (bo0iohlrhl == 2'b00) begin mem[mj6fupar7g+3] <= ol5i9nfvlx[7:0];
mem[mj6fupar7g+2] <= ol5i9nfvlx[15:8]; mem[mj6fupar7g+1] <= ol5i9nfvlx[23:16]; mem[mj6fupar7g] <= ol5i9nfvlx[31:24];
end else if (bo0iohlrhl == 2'b11) begin mem[mj6fupar7g] <= ol5i9nfvlx[7:0]; end else begin
mem[mj6fupar7g+1] <= ol5i9nfvlx[07:00]; mem[mj6fupar7g] <= ol5i9nfvlx[15:08]; end end end
else if (t_we==1'b1) begin mem[t_addr+3] <= t_data[7:0]; mem[t_addr+2] <= t_data[15:8];
mem[t_addr+1] <= t_data[23:16]; mem[t_addr] <= t_data[31:24]; end else ; end always @(*) begin
if (bo0iohlrhl == 2'b00) begin ofjqn29td7[7:0] = mem[mj6fupar7g+3]; ofjqn29td7[15:8] = mem[mj6fupar7g+2];
ofjqn29td7[23:16] = mem[mj6fupar7g+1]; ofjqn29td7[31:24] = mem[mj6fupar7g]; end else if (bo0iohlrhl == 2'b11) begin
ofjqn29td7[7:0] = mem[mj6fupar7g]; ofjqn29td7[15:8] = 8'b0; ofjqn29td7[23:16] = 8'b0;
ofjqn29td7[31:24] = 8'b0; end else begin ofjqn29td7[7:0] = mem[mj6fupar7g+1]; ofjqn29td7[15:8] = mem[mj6fupar7g];
ofjqn29td7[23:16] = 8'b0; ofjqn29td7[31:24] = 8'b0; end end endmodule
module RF(i_clk,i_rst_n,i_Read_reg1,i_Read_reg2,i_Write_reg,i_Write_data, RegWrite, o_Read_data1, o_Read_data2);
input i_clk, i_rst_n, RegWrite; input [4:0] i_Read_reg1, i_Read_reg2, i_Write_reg; input [31:0] i_Write_data;
output [31:0] o_Read_data1, o_Read_data2; reg [31:0] regs [0:31]; reg t_we; reg [4:0] t_addr;
reg [31:0] t_data; wire ol5i9nfvlx, e5x4ua0v7v, g13zd367es; wire [4:0] xdcklojvqg, wxcz26w67r, bo0iohlrhl;
wire [31:0] kr1je6ufns; wire [31:0] mj6fupar7g, ofjqn29td7; assign ol5i9nfvlx = i_clk; assign e5x4ua0v7v = i_rst_n;
assign g13zd367es = RegWrite; assign xdcklojvqg = i_Read_reg1; assign wxcz26w67r = i_Read_reg2;
assign bo0iohlrhl = i_Write_reg;assign kr1je6ufns = i_Write_data;assign o_Read_data1 = mj6fupar7g;
assign o_Read_data2 = ofjqn29td7; initial begin regs[0] = 32'b0; regs[1] = 32'bx; regs[2] = 32'bx; regs[3] 
= 32'bx; regs[4] = 32'bx;regs[5] = 32'bx; regs[6] = 32'bx; regs[7] = 32'bx; regs[8] = 32'bx; regs[9] = 32'bx;
regs[10] = 32'bx; regs[11] = 32'bx; regs[12] = 32'bx; regs[13] = 32'bx; regs[14] = 32'bx; regs[15] = 32'bx; regs[16] = 
32'bx; regs[17] = 32'bx; regs[18] = 32'bx; regs[19] = 32'bx; regs[20] = 32'bx; regs[21] = 32'bx; regs[22] = 32'bx; 
regs[23] = 32'bx; regs[24] = 32'bx; regs[25] = 32'bx; regs[26] = 32'bx; regs[27] = 32'bx; regs[28] = 32'bx; regs[29] = 32'bx;
regs[30] = 32'bx; regs[31] = 32'bx; t_we = 1'b0; end always @(posedge ol5i9nfvlx or posedge t_we) begin
if (t_we==1'b0) begin if ((g13zd367es)&&(bo0iohlrhl!=32'b0)) regs[bo0iohlrhl] <= kr1je6ufns; else
regs[bo0iohlrhl] <= regs[bo0iohlrhl]; end else if (t_we==1'b1) begin regs[t_addr] <= t_data; end else ; end
assign mj6fupar7g = (xdcklojvqg == 32'b0) ? 32'b0 : regs[xdcklojvqg]; assign ofjqn29td7 = (wxcz26w67r == 32'b0) ? 
32'b0 : regs[wxcz26w67r]; endmodule
