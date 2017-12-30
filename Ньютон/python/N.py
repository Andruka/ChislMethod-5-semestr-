# -*- coding: utf-8 -*-
import numpy as np
import math
A=np.zeros((2,2))
F=np.zeros(2)
x_k1=np.zeros(2)
temp_x=np.zeros(2)
x=np.zeros(2)
e=np.zeros(2)
d=np.zeros(2)
e[0]=0.000000001
e[1]=0.000000001
k=[1]
NIT=int(raw_input("Введите максимальное количество итераций\n NIT="))
x[0]=float(raw_input("Введите начальное приближение\n x1="))
x[1]=float(raw_input("Введите начальное приближение\n x2="))
def function1(x):
    	return (x[0]*x[0]-x[1]*x[1]-1)
def function2(x):
    	return (x[0]*x[1]*x[1]*x[1]-x[1]-3)
def derivative11(x):
    	return (2*x[0])
def derivative12(x):
    	return (2*x[1])
def derivative21(x):
    	return (x[1]*x[1]*x[1])
def derivative22(x):
    	return (3*x[0]*x[1]*x[1]-1)
def findMax(A,Max,cur,n):
    Max[0]=cur[0]
    for i in range(cur[0],n):
        if math.fabs(A[Max[0],cur[0]])<math.fabs(A[i,cur[0]]):
            Max[0]=i
def swap(A,F,Max,cur,n):
    findMax(A,Max,cur,n)
    if cur!=Max:
        for i in range(cur[0],n):
            temp=A[Max,i]
            A[Max,i]=A[cur[0],i]
            A[cur[0],i]=temp
        temp=F[Max]
        F[Max]=F[cur[0]]
        F[cur[0]]=temp
    temp=A[cur[0],cur[0]]
    for i in range(cur[0],n):
        for j in range(cur[0],n):
            A[i,j]=A[i,j]/temp
        F[i]=F[i]/temp
def func1(A,F,cur,n):
    for i in range(cur[0]+1,n):
        temp=A[i,cur[0]]
        for j in range(cur[0],n):
            A[i,j]-=A[cur[0],j]*temp
        F[i]-=F[cur[0]]*temp
def gauss1(A,F,Max,cur,n):
    while cur[0]<n-1:
        swap(A,F,Max,cur,n)
        func1(A,F,cur,n)
        cur[0]+=1
def func2(A,F,temp_x,cur,n):
    F1=F[cur[0]]
    if n!=cur[0]:
        for i in range(n-1,cur[0],-1):
            F1-=A[cur[0],i]*temp_x[i]
    temp_x[cur[0]]=F1/A[cur[0],cur[0]]
def gauss2(A,F,temp_x,cur,n):
    while(cur[0]>=0):
        func2(A,F,temp_x,cur,n)
        cur[0]-=1
def calcSLAU(A,F,temp_x,x,x_k1,NIT):
    cur=[0]
    Max=[0]
    n=2
    A[0][0]=derivative11(x)
    A[0][1]=derivative12(x)
    A[1][0]=derivative21(x)
    A[1][1]=derivative22(x)
    F[0]=-1*function1(x)
    F[1]=-1*function2(x)
    gauss1(A,F,Max,cur,n)
    gauss2(A,F,temp_x,cur,n)
    x_k1[0]=x[0]+temp_x[0]
    x_k1[1]=x[1]+temp_x[1]
def checkUsl(d,e,x_k1,x,k):
    temp=0
    if math.fabs(function1(x))>math.fabs(function2(x)):
        d[0]=math.fabs(function1(x))
    else:
        d[0]=math.fabs(function2(x))
    if (math.fabs(x_k1[0]) < 1):
        d[1] = math.fabs(x_k1[0] - x[0]);
    else:
        d[1] = math.fabs((x_k1[0] - x[0])/x_k1[0])
    if (math.fabs(x_k1[1]) < 1):
        temp = math.fabs(x_k1[1] - x[1])
    else:
        temp = math.fabs((x_k1[1] - x[1])/x_k1[1])
    if (temp > d[1]):
        d[1] = temp
    print("%d | %.10f   | %.10f   |"  %(k[0],d[0],d[1]))
    if(d[0]<=e[0] and d[1]<=e[1]):
        return 1
    else: 
        return 0
while True:
    calcSLAU(A,F,temp_x,x,x_k1,NIT)
    if(checkUsl(d,e,x_k1,x,k)):
        break
    if(k[0]>=NIT):
        print("IER=2")
        print(k[0])
        break
    k[0]=k[0]+1
    x[0]=x_k1[0]
    x[1]=x_k1[1]
