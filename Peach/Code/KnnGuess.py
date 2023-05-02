from webbrowser import get
import numpy
import operator

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


#测试#
def dataTest(filename):
    hoRatio = 0.1#测试比例
    [returnMat,classVector] = creatMatrix(filename)#建立数据集
    normMat = numNorm(returnMat)
    m = normMat.shape[0]
    numTestVecs = int(m*hoRatio)
    errorCount = 0.0
    for i in range(numTestVecs):#检测正误
        classifierResult = classifyk(normMat[i,:],normMat[numTestVecs:m,:],classVector[numTestVecs:m],3)
        print("guass:%d\treal:%d\n"%(classifierResult,classVector[i]))
        if(classifierResult != classVector[i]):
            errorCount += 1.0
    print("error rate is:%f"%(errorCount/float(numTestVecs)))

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
    print(classifierResult)

# dataTest("G:\\教育\\e.大三上\\数据科学基础\\Project1\\thePeach.txt")
giveData = [75,119,229]
dataGuess("G:\\教育\\e.大三上\\数据科学基础\\Project1\\thePeach.txt", giveData)