# -*- coding: utf-8 -*-
import numpy as np
import math
import os
from time import time
Max=[0]
cur=[0]
check1=0;
check2=0;
D=[0]
N=int(raw_input("Введите число уравнений:\n N="))
A=np.zeros((N,N))
Y=np.zeros(N)
X=np.zeros(N)
F=np.zeros(N)
while check1!=1 and check1!=2: 
    check1=int(raw_input("Нажмите 1, если хотите ввести уравнения в ручную!\nНажмите 2, если хотите загрузить уравнения из файла!"))
    if check1==1:
        for i in range(N):
            for j in range(N):
                A[i,j]=float(raw_input("Введите A[%d,%d]: "%(i,j)))
            Y[i]=float(raw_input("Введите Y[%d]: "%i))
    if check1==2:
        while check2==0:
            fn=raw_input("Введите имя файла:")
            if os.path.exists(fn):
                check2=1;
                data=np.loadtxt(fn,delimiter=' ',dtype=np.float)
                for i in range(N):
                    for j in range(N):
                        A[i,j]=data[i,j]
                    Y[i]=data[i,N]
            else:
                print("Файл не найден!")
print(A,Y)
Acopy=A.copy()
Ycopy=Y.copy()
def findMax(ar,M,cu,n):
    M[0]=cu[0]
    for i in range(cu[0],n):
        if math.fabs(ar[M[0],cu])<math.fabs(ar[i,cu[0]]):
            M[0]=i
def swap(ar,y,M,cu,n):
    findMax(ar,M,cu,n)
    if cur!=M:
        for i in range(cu[0],N):
            temp=ar[M,i]
            ar[M,i]=ar[cu[0],i]
            ar[cu[0],i]=temp
        temp=y[M]
        y[M]=y[cu[0]]
        y[cu[0]]=temp
    temp=ar[cu[0],cu[0]]
    for i in range(cu[0],n):
        for j in range(cu[0],n):
            ar[i,j]=ar[i,j]/temp
        y[i]=y[i]/temp
def func1(ar,y,cu,n):
    for i in range(cu[0]+1,n):
        temp=ar[i,cu[0]]
        for j in range(cu[0],n):
            ar[i,j]-=ar[cu[0],j]*temp
        y[i]-=y[cu[0]]*temp
def gauss1(ar,y,M,cu,n):
    while(cu[0]<n-1):
        swap(ar,y,M,cu,n)
        func1(ar,y,cu,n)
        cu[0]+=1
def func2(ar,y,x,cu,n):
    y1=y[cu[0]]
    if n!=cu[0]:
        for i in range(n-1,cu[0],-1):
            y1-=ar[cu[0],i]*x[i]
    x[cu[0]]=y1/ar[cu[0],cu[0]]
def gauss2(ar,y,x,cu,n):
    while(cu[0]>=0):
        func2(ar,y,x,cu,n)
        cu[0]-=1
def calcvect(ar,y,x,f,n,d):
    for i in range(n):
        for j in range(n):
            f[i]+=ar[i,j]*x[j]
        f[i]-=y[i]
    d[0]=math.fabs(f[0])
    for i in range(n):
        if d[0]<math.fabs(f[i]):
            d[0]=math.fabs(f[i])
	    print(d[0])
tic=time()
gauss1(A,Y,Max,cur,N)
toc=time()
print("Время работы прямого хода: %f" %(toc-tic))
tic=time()
gauss2(A,Y,X,cur,N)
toc=time()
print("Время работы обратного хода: %f" %(toc-tic))
calcvect(Acopy,Ycopy,X,F,N,D)
print("Решение системы:")
print(X)
print("Вектор невязки: F=Ax*-b")
print(F)
print("Норма:")
print(D[0])
