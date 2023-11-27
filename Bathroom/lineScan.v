module lineScan (l_clk, c_clk, running, change, startor, mode, theRed, theGreen, theLine);//点阵动画处理

	input l_clk;//输入1MHz时钟
	input c_clk;//输入2Hz时钟
	input running;
	input startor;
	input change;
	input [3:0] mode;//模式状态
	
	output reg [7:0] theRed;//红色列点阵
	output reg [7:0] theGreen;//绿色列点阵
	output reg [7:0] theLine;//行点阵
	
	reg [3:0] l_num;//八进制行扫描计数变量
	reg [2:0] c_num;//四进制列动画计数变量
	reg [19:0] slow;//停止计数

	initial @(*) begin//设置为1
		theLine = 8'b11111111;
	end
	
	always @ (posedge l_clk) begin //行扫描
		if(l_num > 3'b111) begin
			theLine = 8'b11111111;
			theLine [0] = 0;
			l_num = 0;
		end
		else begin
			theLine = 8'b11111111;
			theLine [l_num] = 0;
			l_num = l_num + 1;
		end
	end
	
	always @ (posedge c_clk) begin //0.5s计时
		if(c_num > 2'b10) c_num <= 0;
		else c_num <= c_num + 1;
	end
	
	always @ (posedge l_clk) begin //列显示
		if(startor) begin//开机动画
			theGreen = {startor,startor,startor,startor,startor,startor,startor,startor};
			theRed = {startor,startor,startor,startor,startor,startor,startor,startor};
		end
		else
			case(mode)//动画模式检测
				4'b1000://换气模式
					case(c_num)//动画顺序显示
						2'b00:
							case(l_num)//第一个动画
								3'b000: begin theGreen <= 8'b10000111; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b11000110; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b11100100; theRed <= 8'b00000000; end
								3'b011: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b100: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b101: begin theGreen <= 8'b00100111; theRed <= 8'b00000000; end
								3'b110: begin theGreen <= 8'b01100011; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b11100001; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b01:
							case(l_num)//第二个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b011: begin theGreen <= 8'b11111010; theRed <= 8'b00000000; end
								3'b100: begin theGreen <= 8'b01011111; theRed <= 8'b00000000; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								3'b110: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b10:
							case(l_num)//第三个动画
								3'b000: begin theGreen <= 8'b10000111; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b11000110; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b11100100; theRed <= 8'b00000000; end
								3'b011: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b100: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b101: begin theGreen <= 8'b00100111; theRed <= 8'b00000000; end
								3'b110: begin theGreen <= 8'b01100011; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b11100001; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b11:
							case(l_num)//第四个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b011: begin theGreen <= 8'b11111010; theRed <= 8'b00000000; end
								3'b100: begin theGreen <= 8'b01011111; theRed <= 8'b00000000; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								3'b110: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
					endcase
				4'b0100://风暖模式
					case(c_num)//动画顺序显示
						2'b00:
							case(l_num)//第一个动画
								3'b000: begin theGreen <= 8'b11100000; theRed <= 8'b00000111; end
								3'b001: begin theGreen <= 8'b11000000; theRed <= 8'b00000011; end
								3'b010: begin theGreen <= 8'b10100000; theRed <= 8'b00000101; end
								3'b011: begin theGreen <= 8'b00010000; theRed <= 8'b00001000; end
								3'b100: begin theGreen <= 8'b00001000; theRed <= 8'b00010000; end
								3'b101: begin theGreen <= 8'b00000101; theRed <= 8'b10100000; end
								3'b110: begin theGreen <= 8'b00000011; theRed <= 8'b01000000; end
								3'b111: begin theGreen <= 8'b00000111; theRed <= 8'b11100000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b01:
							case(l_num)//第二个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b00011100; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b01000000; end
								3'b011: begin theGreen <= 8'b00001010; theRed <= 8'b11110010; end
								3'b100: begin theGreen <= 8'b00010000; theRed <= 8'b01001111; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00000010; end
								3'b110: begin theGreen <= 8'b00111000; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b10:
							case(l_num)//第三个动画
								3'b000: begin theRed <= 8'b11100000; theGreen <= 8'b00000111; end
								3'b001: begin theRed <= 8'b11000000; theGreen <= 8'b00000011; end
								3'b010: begin theRed <= 8'b10100000; theGreen <= 8'b00000101; end
								3'b011: begin theRed <= 8'b00010000; theGreen <= 8'b00001000; end
								3'b100: begin theRed <= 8'b00001000; theGreen <= 8'b00010000; end
								3'b101: begin theRed <= 8'b00000101; theGreen <= 8'b10100000; end
								3'b110: begin theRed <= 8'b00000011; theGreen <= 8'b01000000; end
								3'b111: begin theRed <= 8'b00000111; theGreen <= 8'b11100000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b11:
							case(l_num)//第四个动画
								3'b000: begin theRed <= 8'b00001000; theGreen <= 8'b00000000; end
								3'b001: begin theRed <= 8'b00011100; theGreen <= 8'b00000000; end
								3'b010: begin theRed <= 8'b00001000; theGreen <= 8'b01000000; end
								3'b011: begin theRed <= 8'b00001010; theGreen <= 8'b11110010; end
								3'b100: begin theRed <= 8'b00010000; theGreen <= 8'b01001111; end
								3'b101: begin theRed <= 8'b00010000; theGreen <= 8'b00000010; end
								3'b110: begin theRed <= 8'b00111000; theGreen <= 8'b00000000; end
								3'b111: begin theRed <= 8'b00010000; theGreen <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
					endcase
				4'b0010://强暖模式
					case(c_num)//动画顺序显示
						2'b00:
							case(l_num)//第一个动画
								3'b000: begin theGreen <= 8'b11100000; theRed <= 8'b11100111; end
								3'b001: begin theGreen <= 8'b11000000; theRed <= 8'b11000011; end
								3'b010: begin theGreen <= 8'b10100000; theRed <= 8'b10100101; end
								3'b011: begin theGreen <= 8'b00010000; theRed <= 8'b00011000; end
								3'b100: begin theGreen <= 8'b00001000; theRed <= 8'b00011000; end
								3'b101: begin theGreen <= 8'b00000101; theRed <= 8'b10100101; end
								3'b110: begin theGreen <= 8'b00000011; theRed <= 8'b01000010; end
								3'b111: begin theGreen <= 8'b00000111; theRed <= 8'b11100111; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b01:
							case(l_num)//第二个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00001000; end
								3'b001: begin theGreen <= 8'b00011100; theRed <= 8'b00011100; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b01001000; end
								3'b011: begin theGreen <= 8'b00001010; theRed <= 8'b11111010; end
								3'b100: begin theGreen <= 8'b00010000; theRed <= 8'b01011111; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00010010; end
								3'b110: begin theGreen <= 8'b00111000; theRed <= 8'b00111000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00010000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b10:
							case(l_num)//第三个动画
								3'b000: begin theRed <= 8'b11100000; theGreen <= 8'b11100111; end
								3'b001: begin theRed <= 8'b11000000; theGreen <= 8'b11000011; end
								3'b010: begin theRed <= 8'b10100000; theGreen <= 8'b00100101; end
								3'b011: begin theRed <= 8'b00010000; theGreen <= 8'b00011000; end
								3'b100: begin theRed <= 8'b00001000; theGreen <= 8'b00011000; end
								3'b101: begin theRed <= 8'b00000101; theGreen <= 8'b10100101; end
								3'b110: begin theRed <= 8'b00000011; theGreen <= 8'b01000010; end
								3'b111: begin theRed <= 8'b00000111; theGreen <= 8'b11100111; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b11:
							case(l_num)//第四个动画
								3'b000: begin theRed <= 8'b00001000; theGreen <= 8'b00001000; end
								3'b001: begin theRed <= 8'b00011100; theGreen <= 8'b00011100; end
								3'b010: begin theRed <= 8'b00001000; theGreen <= 8'b01001000; end
								3'b011: begin theRed <= 8'b00001010; theGreen <= 8'b11111010; end
								3'b100: begin theRed <= 8'b00010000; theGreen <= 8'b01011111; end
								3'b101: begin theRed <= 8'b00010000; theGreen <= 8'b00010010; end
								3'b110: begin theRed <= 8'b00111000; theGreen <= 8'b00111000; end
								3'b111: begin theRed <= 8'b00010000; theGreen <= 8'b00010000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
					endcase
				4'b0001://干燥模式
					case(c_num)//动画顺序显示
						2'b00:
							case(l_num)//第一个动画
								3'b000: begin theGreen <= 8'b10000111; theRed <= 8'b10000000; end
								3'b001: begin theGreen <= 8'b11000110; theRed <= 8'b11000000; end
								3'b010: begin theGreen <= 8'b11100100; theRed <= 8'b11100000; end
								3'b011: begin theGreen <= 8'b00011000; theRed <= 8'b00010000; end
								3'b100: begin theGreen <= 8'b00011000; theRed <= 8'b00001000; end
								3'b101: begin theGreen <= 8'b00100111; theRed <= 8'b00000111; end
								3'b110: begin theGreen <= 8'b01100011; theRed <= 8'b00000011; end
								3'b111: begin theGreen <= 8'b11100001; theRed <= 8'b00000001; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b01:
							case(l_num)//第二个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00001000; end
								3'b001: begin theGreen <= 8'b00011000; theRed <= 8'b00011000; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b00001000; end
								3'b011: begin theGreen <= 8'b11111010; theRed <= 8'b00001000; end
								3'b100: begin theGreen <= 8'b01011111; theRed <= 8'b00010000; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00010000; end
								3'b110: begin theGreen <= 8'b00011000; theRed <= 8'b00011000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00010000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b10:
							case(l_num)//第三个动画
								3'b000: begin theGreen <= 8'b10000111; theRed <= 8'b00000111; end
								3'b001: begin theGreen <= 8'b11000110; theRed <= 8'b00000110; end
								3'b010: begin theGreen <= 8'b11100100; theRed <= 8'b00000100; end
								3'b011: begin theGreen <= 8'b00011000; theRed <= 8'b00001000; end
								3'b100: begin theGreen <= 8'b00011000; theRed <= 8'b00010000; end
								3'b101: begin theGreen <= 8'b00100111; theRed <= 8'b00100000; end
								3'b110: begin theGreen <= 8'b01100011; theRed <= 8'b01100000; end
								3'b111: begin theGreen <= 8'b11100001; theRed <= 8'b11100000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
						2'b11:
							case(l_num)//第四个动画
								3'b000: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b001: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b010: begin theGreen <= 8'b00001000; theRed <= 8'b00000000; end
								3'b011: begin theGreen <= 8'b11111010; theRed <= 8'b11110010; end
								3'b100: begin theGreen <= 8'b01011111; theRed <= 8'b01001111; end
								3'b101: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								3'b110: begin theGreen <= 8'b00011000; theRed <= 8'b00000000; end
								3'b111: begin theGreen <= 8'b00010000; theRed <= 8'b00000000; end
								default: begin theGreen <= 8'b00000000; theRed <= 8'b00000000; end
							endcase
					endcase
				4'b0000://停止模式
					begin
						theGreen <= 8'b00000000; theRed <= 8'b00000000;
					end
				default:begin //默认继续动画
					theGreen <= theGreen;
					theRed <= theRed;
				end
			endcase
	end

endmodule