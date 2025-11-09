class Settings():
    """用一个类来存储外星人入侵的所有设置"""

    def __init__(self):
        """初始化游戏的静态设置"""
        # Screen settings.
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (230, 230, 230)

        # 飞船设置
        self.ship_limit = 3

        # 子弹设置
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = 60, 60, 60
        self.bullets_allowed = 3

        # 外星人设置
        self.fleet_drop_speed = 5

        # 游戏的速度有多快
        self.speedup_scale = 1.1
        # 外星人的增加速度有多快
        self.score_scale = 1.5

        self.initialize_dynamic_settings()

    def initialize_dynamic_settings(self):
        """初始化在整个游戏中改变的设置"""
        self.ship_speed_factor = 1.5  # 1.5
        self.bullet_speed_factor = 3
        self.alien_speed_factor = 0.5 # 1

        # 击败每一个外星人的分数
        self.alien_points = 50

        # 舰队方向 1 代表右边 -1代表左边
        self.fleet_direction = 1

    def increase_speed(self):
        """增加速度设置和外星人价值"""
        self.ship_speed_factor *= self.speedup_scale
        self.bullet_speed_factor *= self.speedup_scale
        self.alien_speed_factor *= self.speedup_scale

        self.alien_points = int(self.alien_points * self.score_scale)
