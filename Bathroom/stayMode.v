module stayMode(clk, clk2H, openit, number, tube, stay, running, ware, seg_data, normal);//待机模式

	input clk;
	input clk2H;
	input openit;//开关
	input [3:0] seg_data;
	input normal;
	
	output [6:0] number;//七段数码管显示
	output [7:0] tube;//八个数码管
	output reg stay;//进入待机模式
	output reg running;//正在进入待机模式
	output reg ware = 0;//开机状态变量
	
	reg [3:0] times = 0;//计数变量
	reg [8:0] seg [9:0];
	reg [3:0] gooo;
	
	initial
	    begin
         seg[0] = 9'h3f;//7段显示数字  0
	      seg[1] = 9'h06;//7段显示数字  1
	      seg[2] = 9'h5b;//7段显示数字  2
	      seg[3] = 9'h4f;//7段显示数字  3
	      seg[4] = 9'h66;//7段显示数字  4
	      seg[5] = 9'h6d;//7段显示数字  5
	      seg[6] = 9'h7d;//7段显示数字  6
	      seg[7] = 9'h07;//7段显示数字  7
	      seg[8] = 9'h7f;//7段显示数字  8
	      seg[9] = 9'h6f;//7段显示数字  9
			gooo = 4'b1000;
        end
	
	always @ (posedge clk2H) begin//四进制波形发生器
		if(openit)
			if(times > 4'b0111) begin//计数器
				ware <= 0;
				stay <= 1;
				running <= 0;
				gooo <= 0;
			end
			else begin
				times <= times + 1;
				running <= 1;
				ware <= ~ware;
			end
		else begin//关机
			gooo <= 4'b1000;
			times <= 0;
			ware <= 0;
			running <= 0;
			stay <= 0;
		end
	end
			
	assign tube = ~{ware,ware,ware,ware|normal,ware,ware,ware,ware};
	assign number = seg[seg_data|gooo];
	
endmodule