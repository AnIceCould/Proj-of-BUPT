###带接口整合RGB成熟度判断
##input1:图片地址 94行
##input2:一个数字 95行 桃子种类 0为八五 1为九零
##output:成熟度 120行 1成熟 2较成熟 3未成熟

from webbrowser import get
import numpy
import operator
import sys,os
import cv2
import math

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
    zimg = numpy.zeros((h, w, 1), numpy.uint8)
    re_pic = cv2.circle(zimg, (w2,h2), min(h2,w2)-20, 255,-1)
    return re_pic

#读取文本数据#
def creatMatrix(filename):
    theFile = open(filename)
    arrayLine = theFile.readlines()
    arrayLen = len(arrayLine)
    returnMat = numpy.zeros((arrayLen,3))#生成N*3矩阵
    index = 0
    classVector = []
    for line in arrayLine:#构建数据坐标及其对应标签
        line = line.strip()
        listFromLine = line.split('\t')
        returnMat[index,:] = listFromLine[0:3]#三维数据
        classVector.append(int(listFromLine[-1]))#标签(数字对应)
        index += 1
    return returnMat,classVector

#数值归一化#
def numNorm(oldData):
    minValue = oldData.min(0)
    maxValue = oldData.max(0)
    ranges = maxValue - minValue
    normDate = numpy.zeros(numpy.shape(oldData))
    m = oldData.shape[0]
    normDate = oldData - numpy.tile(minValue,(m,1))
    normDate = normDate/numpy.tile(ranges,(m,1))
    return normDate, minValue, maxValue
    
#kNN算法#
def classifyk(inX,dataSet,labels,k):
    '''
    inX：用来分类的测试集
    dataSet：用来训练的数据集
    labels：用来训练的数据集的标签
    k：k近邻的k值
    '''
    dataSetSize = dataSet.shape[0]
    diffMat = numpy.tile(inX,(dataSetSize,1)) - dataSet
    sqDiffMat = diffMat**2
    sqDistances = sqDiffMat.sum(axis = 1)
    distances = sqDistances**0.5
    sortedDistIndicies = distances.argsort()
    classCount = {}
    for i in range(k):#选择距离最小的k个点
        voteIlabe = labels[sortedDistIndicies[i]]
        classCount[voteIlabe] = classCount.get(voteIlabe,0) + 1
    sortedClassCount = sorted(classCount.items(),key=operator.itemgetter(1),reverse=True)#排序
    return sortedClassCount[0][0]

#单位猜测
def dataGuess(filename, dataInf):
    '''
    filename:数据集地址
    dataInf:待猜测数据[B,G,R]
    '''
    [returnMat,classVector] = creatMatrix(filename)#建立数据集
    returnMat = numNorm(returnMat)
    normMat = returnMat[0]
    #数值归一化
    minNum = returnMat[1]
    maxNum = returnMat[2]
    testMat = (dataInf-minNum)/(maxNum-minNum)
    classifierResult = classifyk(testMat,normMat,classVector,3)
    return(classifierResult)

#文件位置定义区
filePath = '../Pic/before.png' #输入接口：图片地址
pattern = 0 #输入接口：桃子类型
data90Path = "../Data/90data.txt" #存放90桃子数据的地址
data85Path = "../Data/85data.txt" #存放85桃子数据的地址
outPath = '../Pic/after.jpg' #输出裁剪后图片 调试用

#处理区
image = cv2.imread(filePath)
matPic = oneFtwo(image) #中心裁剪
outImg = cv2.bitwise_and(image,image,mask=matPic) #按位与(带蒙版)
#cv2.imwrite(outPath, outImg) #调试用 使用时请注释掉
mean1 = cv2.mean(outImg,matPic) #得出平均RGB值
mean2 = [0,0,0]
mean2[0] = round(mean1[0])
mean2[1] = round(mean1[1])
mean2[2] = round(mean1[2])
#print(mean2) #平均BGR

#猜测区
if pattern == 1:
    dataPath = data90Path
else:
    dataPath = data85Path
outPut = dataGuess(dataPath, mean2)

#输出接口
print(outPut)