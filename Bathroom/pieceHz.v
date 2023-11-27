module pieceHz (clk, clk_p, set_clock);//1MHz --> xHz分频器

	input clk;//原始时钟1MHz
	input [19:0] set_clock;//输入20位分频值
	output reg clk_p;//分频时钟
	
	reg [19:0] t_num;//储存系数

	initial @(*) begin
		clk_p <= 0;
		t_num <= 0;
	end
	always @ (posedge clk) begin //计数器

		if(t_num >= set_clock) begin
			t_num <= 0;
			clk_p <= ~clk_p;
		end
		else begin
			t_num <= t_num + 1;
			clk_p <= clk_p;
		end
	end

endmodule
