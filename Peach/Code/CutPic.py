# coding=gbk
###ͼ����###
###ͼ����ת�Լ�����ü��������ݼ�##

import os
import cv2
from PIL import Image

##����
filePath = 'G:/IceCould/Total/InternetPlus/�������ݼ�������ǣ�/��ȡ'
outPath = 'G:/IceCould/Total/InternetPlus/�������ݼ�������ǣ�/��ת/'
thefilelist = os.listdir(filePath)

##��ת
for i in thefilelist:
    img = Image.open(filePath + '/' + i)
    img = img.transpose(Image.ROTATE_90) #��ͼƬ��ת90��
    img.save(outPath + i[0:-4] + 'a.png')
    img = img.transpose(Image.ROTATE_180) #��ͼƬ��ת180��
    img.save(outPath + i[0:-4] + 'b.png')
    img = img.transpose(Image.ROTATE_270) #��ͼƬ��ת270��
    img.save(outPath + i[0:-4] + 'c.png')


##�ü�
'''
img2 = cv2.imread("G:/IceCould/Total/InternetPlus/Code/L/rotate9.png")
cropped = img2[100:620, 100:620] #����Ϊ[y0:y1, x0:x1]
cv2.imwrite("FG:/IceCould/Total/InternetPlus/Code/L/cutR.png", cropped)
'''