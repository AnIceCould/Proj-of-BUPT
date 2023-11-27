module modeSet(clk, clk_t, switch, cando, running, startor, mode, light, slow, normal);//动画模式切换和灯光显示

	input clk;
	input clk_t;//计时时钟
	input cando;//开关
	input running;
	input startor;
	input [4:0] switch;//五个按钮
	
	output reg [3:0] mode;//模式输出
	output reg [15:0] light;//灯光输出
	output reg normal;
	
	reg change;//切换状态
	reg stopout;//结束输出
	reg led;//照明开关
	reg case_res;//状态存储
	output reg [3:0] slow;//计数
	reg change_r;
	
	initial
		slow = 4'b1000;
	
	always @ (posedge clk) begin//模式切换
		
		case(switch[4:1])
			4'b1000:
				if(!change)
					if(mode == 4'b1000) change <= 1;
					else begin
						mode <= 4'b1000;
						change <= 0;
					end
			4'b0100:
				if(!change)
					if(mode == 4'b0100) change <= 1;
					else begin
						mode <= 4'b0100;
						change <= 0;
					end
			4'b0010:
				if(!change)
					if(mode == 4'b0010) change <= 1;
					else begin
						mode <= 4'b0010;
						change <= 0;
					end
			4'b0001:
				if(!change)
					if(mode == 4'b0001) change <= 1;
					else begin
						mode <= 4'b0001;
						change <= 0;
					end
			4'b0000:begin
				change <= 0;
			end
		endcase
		if(stopout) //结束
			mode <= 4'b0000;
	end
	
	always @ (posedge clk_t) begin//第二次按键
		if(change || change_r) begin
			change_r <= ~stopout;
			case(mode)
				4'b0100: begin//待机2s
					if(slow == 0) begin
						stopout <= 1;
						normal <= 0;
					end
					else begin
						slow <= slow - 1;
						normal <= 1;
					end
				end
				4'b0010: begin//待机4s
					if(slow == 0) begin
						stopout <= 1;
						normal <= 0;
					end
					else begin
						slow <= slow - 1;
						normal <= 1;
					end
				end
				default: stopout <= 1;//直接停止
			endcase
		end
		else begin
			stopout <= 0;
			case(mode)
				4'b0010:slow <= 4'b1000;
				4'b0100:slow <= 4'b0100;
			endcase
		end
	end
	
	/*always @ (posedge clk)//开机灯光动画
		if(running) begin
			light <= {startor,startor,startor,startor,startor,startor,startor,startor,startor,startor||led,startor,startor,startor,startor,startor,startor};
		end
		else light <= light;
	
	always @ (negedge switch[0])//照明模式
		if(switch[0])
			led <= ~led;
		else if(!cando) led <= 0;
		else led <= led;*/

		always @ (posedge clk or posedge switch[0]) begin
			if(switch[0])//照明模式
				light[6] <= ~light[6];
			else if(running)//开机灯光动画
				light <= {startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor,startor};
			else if(!cando) light <= 0;
			else light <= light;
		end
	
endmodule