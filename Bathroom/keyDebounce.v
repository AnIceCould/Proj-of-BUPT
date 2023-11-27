module keyDebounce (clk1M, clk20, key, key_pulse);// 按键消抖
	
	input clk1M;//系统时钟1MHz
	input clk20;//延时时钟20ms
	input [N-1:0] key;//输入的按键					
	
	output  [N-1:0]   key_pulse;//按键动作产生的脉冲	
	
	parameter N = 5;//要消除的按键的数量
	
	reg [N-1:0] key_rst_pre;//存上一个触发时的按键值
	reg [N-1:0] key_rst;//存储当前时刻触发的按键值
	
 
	always @(posedge clk20) begin //储存当前值和前一个值
			key_rst <= key;
			key_rst_pre <= key_rst;
	end
 
	assign  key_pulse = key_rst_pre & key_rst;//两个值均为1  
 
endmodule