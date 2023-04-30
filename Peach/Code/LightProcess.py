# coding=gbk
###ͼ����###
###���չ�һ��##

import sys,os
import numpy as np
import argparse
import cv2

def hisColor_Img(path):
    """
    ��ͼ��ֱ��ͼ���⻯
    :param path: ͼƬ·��
    :return: ֱ��ͼ���⻯���ͼ��
    """
    img = cv2.imread(path)
    ycrcb = cv2.cvtColor(img, cv2.COLOR_BGR2YCR_CB)
    channels = cv2.split(ycrcb)
    cv2.equalizeHist(channels[0], channels[0]) #equalizeHist(in,out)
    cv2.merge(channels, ycrcb)
    img_eq=cv2.cvtColor(ycrcb, cv2.COLOR_YCR_CB2BGR)
    return img_eq

def clahe_Img(path,ksize):
    """
    :param path: ͼ��·��
    :param ksize: ����ֱ��ͼ���⻯�������С,Ĭ��Ϊ8
    :return: clahe֮���ͼ��
    """
    image = cv2.imdecode(np.fromfile(path, dtype=np.uint8),-1)#����·��
    #image = cv2.imread(path, cv2.IMREAD_COLOR)#Ӣ��·��
    b, g, r = cv2.split(image)
    clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(ksize,ksize))
    b = clahe.apply(b)
    g = clahe.apply(g)
    r = clahe.apply(r)
    image = cv2.merge([b, g, r])
    return image

def whiteBalance_Img(path):
    """
    ��ƽ��
    """
    img = cv2.imread(path)
    b, g, r = cv2.split(img)
    Y = 0.299 * r + 0.587 * g + 0.114 * b
    Cr = 0.5 * r - 0.419 * g - 0.081 * b
    Cb = -0.169 * r - 0.331 * g + 0.5 * b
    Mr = np.mean(Cr)
    Mb = np.mean(Cb)
    Dr = np.var(Cr)
    Db = np.var(Cb)
    temp_arry = (np.abs(Cb - (Mb + Db * np.sign(Mb))) < 1.5 * Db) & (
                np.abs(Cr - (1.5 * Mr + Dr * np.sign(Mr))) < 1.5 * Dr)
    RL = Y * temp_arry
    # ѡȡ��ѡ�׵���������10%ȷ��Ϊ���հ׵㣬��ѡ����ǰ10%�е���С����ֵ
    L_list = list(np.reshape(RL, (RL.shape[0] * RL.shape[1],)).astype(np.int))
    hist_list = np.zeros(256)
    min_val = 0
    sum = 0
    for val in L_list:
        hist_list[val] += 1
    for l_val in range(255, 0, -1):
        sum += hist_list[l_val]
        if sum >= len(L_list) * 0.1:
            min_val = l_val
            break
    # ȡ������ǰ10%Ϊ���յİ׵�
    white_index = RL < min_val
    RL[white_index] = 0
    # ����ѡȡΪ�׵��ÿ��ͨ��������
    b[white_index] = 0
    g[white_index] = 0
    r[white_index] = 0
    Y_max = np.max(RL)
    b_gain = Y_max / (np.sum(b) / np.sum(b > 0))
    g_gain = Y_max / (np.sum(g) / np.sum(g > 0))
    r_gain = Y_max / (np.sum(r) / np.sum(r > 0))
    b, g, r = cv2.split(img)
    b = b * b_gain
    g = g * g_gain
    r = r * r_gain
    # �������
    b[b > 255] = 255
    g[g > 255] = 255
    r[r > 255] = 255
    res_img = cv2.merge((b, g, r))
    return res_img

def blue_Img(imgpath):
    '''
    ���Ⱦ��⣨�ϰ���
    '''
    image = cv2.imread(imgpath)
    (B, G, R) = cv2.split(image)
    imageBlueChannelAvg = np.mean(B)
    imageGreenChannelAvg = np.mean(G)
    imageRedChannelAvg = np.mean(R)
    K = (imageRedChannelAvg+imageGreenChannelAvg+imageRedChannelAvg)/3
    Kb = K/imageBlueChannelAvg
    Kg = K/imageGreenChannelAvg
    Kr = K/imageRedChannelAvg
    B = cv2.addWeighted(B, Kb, 0, 0, 0)
    G = cv2.addWeighted(G, Kg, 0, 0, 0)
    R = cv2.addWeighted(R, Kr, 0, 0, 0)
    return cv2.merge([B, G, R])

'''
�㷨����

photo = "G:/IceCould/Total/InternetPlus/Code/Pic/20(1).png"#����ͼƬ
A = hisColor_Img(photo)
cv2.imwrite("G:/IceCould/Total/InternetPlus/Code/A.png", A)
B = clahe_Img(photo, 8)##Ч�����
cv2.imwrite("G:/IceCould/Total/InternetPlus/Code/B.png", B)
C = whiteBalance_Img(photo)
cv2.imwrite("G:/IceCould/Total/InternetPlus/Code/C.png", C)
D = blue_Img(photo)
cv2.imwrite("G:/IceCould/Total/InternetPlus/Code/D.png", D)
'''

'''
��������
'''
##����
#filePath = 'G:/IceCould/Total/InternetPlus/Test/initial/32' #Ӣ��·��
#����·��
osChar = sys.getdefaultencoding()
filePath = 'G:\\IceCould\\Total\InternetPlus\\Test\\initial\\nine\\'
outPath = 'G:/IceCould/Total/InternetPlus/Test/last/nine'
thefilelist = os.listdir(filePath)
#print(thefilelist)
for i in thefilelist:
    img = os.path.join('G:',os.sep,filePath[3:-1],i) #����·��
    #img = filePath + '/' + i #Ӣ��·��
    B = clahe_Img(img, 8)
    #cv2.imwrite(outPath + '/' + i, B) #Ӣ��·��
    cv2.imencode('.jpg', B)[1].tofile(outPath + '/' + i[0:-4] + '.jpg')  #����·����jpg��ʽ��
