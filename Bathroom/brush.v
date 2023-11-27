//--------------------
module brush (clk1M, switch, openBush, seven, tube, red, green, line, light);//模拟风暖式浴霸控制器

	input clk1M;//原始1MHz 时钟位置：0101
	input [4:0] switch;//五个按钮
	input openBush;//开关
	
	output [6:0] seven;//七段数码管显示
	output [7:0] tube;//八个数码管
	output [7:0] red;//红色列点阵
	output [7:0] green;//绿色列点阵
	output [7:0] line;//行点阵
	output [15:0] light;//灯光输出（6为浴室灯）
	
	wire clk2H;//分频2Hz（动画时钟）
	wire clk50H;//分频50Hz（消抖时钟）
	wire [4:0] key_p;//消抖后按钮
	wire [3:0] mode;//模式状态
	wire stay;//进入待机模式
	wire running;//正在进入待机模式
	wire startor;//开机动画记录变量
	wire [1:0] change;//记录点阵之前状态
	wire [3:0] seg_data;//数码管输出
	wire normal;
	
	/*1MHz --> 2Hz分频器实例化*/
	pieceHz TimeTwo(
		.clk(clk1M),
		.set_clock(20'b0001_1110_1000_0100_1000),//2Hz参数
		.clk_p(clk2H)
	);
	
	/*1MHz --> 50Hz分频器实例化*/
	pieceHz TimeFive(
		.clk(clk1M),
		.set_clock(20'b0000_0001_0011_1000_1000),//50Hz参数20'b0000_0001_0011_1000_1000
		.clk_p(clk50H)
	);
	
	/*待机状态和数码管动画*/
	stayMode DaiJi(
		.clk(clk1M),
		.clk2H(clk2H),
		.openit(openBush),
		.seg_data(seg_data),
		.number(seven),
		.tube(tube),
		.stay(stay),
		.running(running),
		.ware(startor),
		.normal(normal)
	);
	
	/*点阵动画*/
	lineScan DongHua(
		.l_clk(clk1M),
		.c_clk(clk2H),
		.running(running),
		.startor(startor),
		.mode(mode),
		.theRed(red),
		.theGreen(green),
		.theLine(line)
	);

	/*模式切换和灯光动画*/
	modeSet QieHuan(
		.clk(clk1M),
		.clk_t(clk2H),
		.switch(key_p),
		.cando(stay),
		.running(running),
		.startor(startor),
		.mode(mode),
		.light(light),
		.slow(seg_data),
		.normal(normal)
	);
	
	/*按键消抖*/
	keyDebounce XiaoDou(
		.clk1M(clk1M),
		.clk20(clk50H),
		.key(switch),
		.key_pulse(key_p)
	);
	
	
endmodule
