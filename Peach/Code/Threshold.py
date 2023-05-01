###阈值分割算法###
###按标注裁剪###
###RGB统计###

import sys,os
import numpy as np
import cv2
import math


def threshold_two_peak(image):
    """
    阈值分割
    image:输入图片
    threshImage:输出图片
    """
    # 计算灰度直方图
    histogram = calcGrayHist(image)
    # 找到灰度直方图的最大峰值对应的灰度值
    maxLoc = np.where(histogram==np.max(histogram))
    firstPeak = maxLoc[0][0]
    # 寻找灰度直方图的第二个峰值对应的灰度值
    measureDists = np.zeros([256], np.float32)
    for k in range(256):
        measureDists[k] = pow(k-firstPeak, 2) * histogram[k]
    maxLoc2 = np.where(measureDists==np.max(measureDists))
    secondPeak = maxLoc2[0][0]
    # 找到两个峰值之间的最小值对应的灰度值，作为阈值
    thresh = 0
    if firstPeak > secondPeak:  # 第一个峰值在第二个峰值的右侧
        temp = histogram[int(secondPeak):int(firstPeak)]
        minLoc = np.where(temp==np.min(temp))
        thresh = secondPeak + minLoc[0][0] + 1
    else:                       # 第一个峰值在第二个峰值的右侧
        temp = histogram[int(firstPeak):int(secondPeak)]
        minLoc = np.where(temp==np.min(temp))
        thresh = firstPeak + minLoc[0][0] + 1
    # 找到阈值后进行阈值处理，得到二值图
    threshImage = image.copy()
    threshImage[threshImage>thresh] = 255
    threshImage[threshImage<=thresh] = 0
    return threshImage

def calcGrayHist(I):
    '''
    计算灰度直方图
    I:输入图片
    grayHist:输出直方图数组
    '''
    h, w = I.shape[:2]
    grayHist = np.zeros([256], np.uint64)
    for i in range(h):
        for j in range(w):
            grayHist[I[i][j]] += 1
    return grayHist

def oneFtwo(pre_pic):
    '''
    以中心为基准二分之一圆蒙版
    pre_pic:原始图片
    re_pic:预设好的二分圆蒙版
    '''
    size = pre_pic.shape
    w = size[1]
    h = size[0]
    w2 = round(w/2)
    h2 = round(h/2)
    #获得中心蒙版
    zimg = np.zeros((h, w, 1), np.uint8)
    re_pic = cv2.circle(zimg, (w2,h2), min(h2,w2)-20, 255,-1)
    return re_pic

def formatCut(picName, pic, path):
    '''
    根据yolo标注信息裁剪
    pic:待裁剪照片名称
    '''
    #获取文件
    txtName = picName[0:-3] + 'txt'
    formatFile = open(path + '/' + txtName,'r')
    formatText = formatFile.readline()
    #行切片：中心比值XY；框大小WH
    centerX = float(formatText[2:7])
    centerY = float(formatText[11:16])
    cubeW = float(formatText[20:25])
    cubeH = float(formatText[29:34])
    #黑色图片
    size = pic.shape
    w = size[1]
    h = size[0]
    zimg = np.zeros((h, w, 1), np.uint8)
    #画圆
    radius = min(round(cubeW*w), round(cubeH*h))
    ffPic = cv2.circle(zimg, (round(centerX*w), round(centerY*h)), round(radius/2), (255,255,255), -1)

    formatFile.close()
    return ffPic


filePath = 'G:/Temp/14_390'
outPath = 'G:/Temp/after'
fileName1 = 'G:/Temp/B.txt'
fileName2 = 'G:/Temp/G.txt'
fileName3 = 'G:/Temp/R.txt'
thefilelist = os.listdir(filePath)



#批量处理过程
'''
img:图片路径
image:图片data
matPic:按标注蒙版
test_pic:按中心蒙版
thimg:阈值分割蒙版
outimg:合并蒙版后图片
'''
for i in thefilelist:
    #获取图片及其灰度图
    img = filePath + '/' + i #英文路径
    image = cv2.imread(img)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) #灰度化的图像

    #按模型裁剪
    matPic = formatCut(i, image, 'G:/Temp/ttt')
    outimg = cv2.bitwise_and(image,image,mask=matPic) #按位与(带蒙版)
    #cv2.imwrite(outPath + '/' + i, outimg)
    
#     #中心裁剪
#     test_pic = oneFtwo(image)
#     outimg = cv2.bitwise_and(image,image,mask=test_pic) #按位与(带蒙版)
#     cv2.imwrite(outPath+ '/' + i,outimg)
    
#
#     #合并阈值分割
#     thimg = threshold_two_peak(gray) #阈值分割的蒙版
#     outimg = cv2.bitwise_and(image,image,mask=thimg) #按位与(带蒙版)
#     #cv2.imwrite(outPath+ '/' + i,outimg)
#

    #得出平均RGB值
    mean1 = cv2.mean(outimg,matPic)
    #B
    theFile = open(fileName1,'a')
    theFile.write(str(round(mean1[0])))
    theFile.write('\n')
    theFile.close()
    #G
    theFile = open(fileName2,'a')
    theFile.write(str(round(mean1[1])))
    theFile.write('\n')
    theFile.close()
    #R
    theFile = open(fileName3,'a')
    theFile.write(str(round(mean1[2])))
    theFile.write('\n')
    theFile.close()

