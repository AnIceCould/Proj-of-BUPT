import pygame
from pygame.sprite import Sprite


class Ship(Sprite):

    def __init__(self, ai_settings, screen):
        """初始化飞船，并设置其起始位置"""
        super(Ship, self).__init__()
        self.screen = screen
        self.ai_settings = ai_settings

        # 加载飞船图像，并得到它的rect。
        self.image = pygame.image.load('images/ship.bmp')
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

        # 在屏幕底部的中心开始每一艘新飞船
        self.rect.centerx = self.screen_rect.centerx
        self.rect.bottom = self.screen_rect.bottom

        # 为飞船的中心储存一个十进制值
        self.center = float(self.rect.centerx)

        # 运动标记
        self.moving_right = False
        self.moving_left = False

    def center_ship(self):
        """把船放在屏幕"""
        self.center = self.screen_rect.centerx

    def update(self):
        """根据移动标志更新船的位置"""
        # 更新船的中心值，而不是rect
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.center += self.ai_settings.ship_speed_factor
        if self.moving_left and self.rect.left > 0:
            self.center -= self.ai_settings.ship_speed_factor

        # 从self.center更新为rect对象
        self.rect.centerx = self.center

    def blitme(self):
        """在其当前位置绘制飞船"""
        self.screen.blit(self.image, self.rect)
