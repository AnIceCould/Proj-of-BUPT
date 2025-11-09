import pygame
from pygame.sprite import Sprite


class Alien(Sprite):
    """一个在舰队中代表一个外星人的类。"""

    def __init__(self, ai_settings, screen):
        """初始化外星人，并设置它的起始位置"""
        super(Alien, self).__init__()
        self.screen = screen
        self.ai_settings = ai_settings

        # 加载异形图像，并设置其rect属性。
        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect()

        # 在屏幕左上方开始每一个新的外星人
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        # 储存外星人的确切位置
        self.x = float(self.rect.x)

    def check_edges(self):
        """如果外星人在屏幕边缘，返回True"""
        screen_rect = self.screen.get_rect()
        if self.rect.right >= screen_rect.right:
            return True
        elif self.rect.left <= 0:
            return True

    def update(self):
        """左右移动外星人"""
        self.x += (self.ai_settings.alien_speed_factor *
                   self.ai_settings.fleet_direction)
        self.rect.x = self.x

    def blitme(self):
        """在其当前位置绘制外星人"""
        self.screen.blit(self.image, self.rect)
