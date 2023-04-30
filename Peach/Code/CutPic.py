# coding=gbk
###图像处理###
###图像旋转以及随机裁剪扩充数据集##

import os
import cv2
from PIL import Image

##遍历
filePath = 'G:/IceCould/Total/InternetPlus/澳油数据集（待标记）/截取'
outPath = 'G:/IceCould/Total/InternetPlus/澳油数据集（待标记）/旋转/'
thefilelist = os.listdir(filePath)

##旋转
for i in thefilelist:
    img = Image.open(filePath + '/' + i)
    img = img.transpose(Image.ROTATE_90) #将图片旋转90度
    img.save(outPath + i[0:-4] + 'a.png')
    img = img.transpose(Image.ROTATE_180) #将图片旋转180度
    img.save(outPath + i[0:-4] + 'b.png')
    img = img.transpose(Image.ROTATE_270) #将图片旋转270度
    img.save(outPath + i[0:-4] + 'c.png')


##裁剪
'''
img2 = cv2.imread("G:/IceCould/Total/InternetPlus/Code/L/rotate9.png")
cropped = img2[100:620, 100:620] #坐标为[y0:y1, x0:x1]
cv2.imwrite("FG:/IceCould/Total/InternetPlus/Code/L/cutR.png", cropped)
'''