from sklearn.decomposition import PCA
import numpy as np
from matplotlib import pyplot as plt


K = 6
oriData = []
nameArr = []

#############################################################################
#파일 읽기

fp1 = open("./etf_cp_list.txt","r")
fp2 = open("./etf_list.txt","r")

while True:
    codeLine = fp2.readline().strip()
    if not codeLine: break

    cpLine = fp1.readline().strip()
    if not cpLine: 
        cpLine = fp1.readline().strip()

    t = list()
    for i in cpLine.split(' '):
        t.append(i)
    oriData.append(t)
    nameArr.append(codeLine.split(' ')[1:3])

fp1.close()
fp2.close()

fp1 = open("./krx300_cp_list.txt","r")
fp2 = open("./krx300_list.txt","r")

while True:
    codeLine = fp2.readline().strip()
    if not codeLine: break

    cpLine = fp1.readline().strip()
    if not cpLine: 
        cpLine = fp1.readline().strip()

    t = list()
    for i in cpLine.split(' '):
        t.append(i)
    oriData.append(t)
    nameArr.append(codeLine.split(' ')[1:3])


fp1.close()
fp2.close()

#############################################################################
#종가전처리(일간변화율)   #((당일종가/전일종가)-1)*100    #첫날변화율0

data = []
for i in oriData:
    t = list()
    temp = int(i[0])
    for j in i:
        t.append(100*((int(j)/temp)-1))
        temp = int(j)
    data.append(t)

#############################################################################
#feature추출 #차원축소 #PCA
pca = PCA(n_components = 60) #주성분의 수
feature = pca.fit_transform(data)

#print(sum(pca.explained_variance_ratio_))

#############################################################################
#K-means clustering
# 초기 벡터 0으로 초기화
v = []
for i in range(K):
    v.append([0.0 for j in range(60)])

group = [8 for j in data]
F = np.array(feature)
V = np.array(v)

change = 1; count = 0
while change:
    change = 0 #종료조건
    count= count +1 #종료조건
    if count > 200: break

    # 유클리드 거리 계산, clustering
    for i in range(len(oriData)): #i는 60개의 주성분 리스트
        m= 0; g = 0; d=[]
        for j in range(K):
            #i와 j사이의 거리가 최소인 것으로 라벨링
            d.append(np.sum((F[i]-V[j])**2))
        if group[i]!=np.argmin(d): #분류가 변화한 항목이 존재함
            change =1
            group[i] = np.argmin(d);

    #새 벡터값 결정(평균)
    for i in range(K):
        T = np.array([0 for j in range(60)])
        for j in range(len(oriData)):
            if group[j]!=i:continue
            T = T+F[j]
        V[i] = T/60

#############################################################################
#Beta 계수 계산
#############################################################################
#결과 출력
x = list(range(len(oriData[0])))
for i in range(K):
    count = 0
    print(i,"Cluster")
    y=[]
    for j in range(len(oriData)):
        if group[j]!=i:continue
        #i그룹에 속하는 종목명 출력
        print(nameArr[j])
        if(count<5):
            t = list()
            for u in range(len(oriData[0])): 
                t.append(oriData[j][u])
                #t.append(data[j][u])
            y.append(t)
        count = count+1
    if(count < 5): a = count
    else: a = 5
    for j in range(a):
        plt.plot(x,y[j])
    print(count, "\n\n\n\n")
    plt.show()
