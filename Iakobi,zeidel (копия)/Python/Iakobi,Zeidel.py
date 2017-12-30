# -*- coding: utf-8 -*-
import numpy as np
from math import fabs
import os
import re
import sys

def checkUslovie(A,N):
    num=0
    summ=0
    for i in range(N):
        num=fabs(A[i][i])
        for j in range(N):
            if i!=j:
                summ=summ+fabs(A[i][j])
        if num<summ:
            print("Условие диагонального преобладания не выполнено!")
            sys.exit()
        summ=0
def findX(method,A,Y,X,tempX,N):
    if method==1:
        for i in range(N):
            X[i]=Y[i]
            for j in range(N):
                if i!=j:
                    X[i]=X[i]-A[i][j]*tempX[j]
            X[i]=X[i]/A[i][i]
    if method==2:
        for i in range(N):
            X[i]=Y[i]
            for j in range(i):
                if i!=j:
                    X[i]=X[i]-A[i][j]*X[j]
            for j in range(i,N):
                if i!=j:
                    X[i]=X[i]-A[i][j]*tempX[j]
            X[i]=X[i]/A[i][i]
def func(E,method,A,Y,X,tempX,N,iterat):
    Max=0
    while 1:
        findX(method,A,Y,X,tempX,N)
        iterat[0]+=1
        Max=fabs(X[0]-tempX[0])
        for i in range(1,N):
            if Max<fabs(X[i]-tempX[i]):
                Max=fabs(X[i]-tempX[i])
        if Max<E:
            return
        for i in range(N):
            tempX[i]=X[i]
check1=0;
check2=0;
iterat=[0]
N=int(raw_input("Введите число уравнений:\n N="))
E=float(raw_input("Введите точность:\n E="))
A=np.zeros((N,N))
Y=np.zeros(N)
X=np.zeros(N)
tempX=np.zeros(N)
while check1!=1 and check1!=2: 
    check1=int(raw_input("Нажмите 1, если хотите ввести уравнения в ручную!\nНажмите 2, если хотите загрузить уравнения из файла!"))
    if check1==1:
        for i in range(N):
            for j in range(N):
                A[i][j]=float(raw_input("Введите A[%d,%d]: "%(i,j)))
            Y[i]=float(raw_input("Введите Y[%d]: "%i))
    if check1==2:
        while check2==0:
            fn=raw_input("Введите имя файла:")
            if os.path.exists(fn):
                check2=1;
                file = open(fn)
                text=file.readlines()
                if len(text)!=N:
                    print("Неверный формат файла!")
                    sys.exit()
                for i in range(N):
                    arr=re.findall(r"[-]?\d+\.\d+|[-]?\d+", text[i])
                    if len(arr)!=N+1:
                        print("Неверный формат файла!")
                        sys.exit()
                    else:
                        for j in range(N):
                            A[i][j]=arr[j]
                        Y[i]=arr[N]
            else:
                print("Файл не найден!")
                sys.exit()
checkUslovie(A,N)
print("Матрица коеффициентов:")
print(A)
print("Матрица b:")
print(Y)
func(E,1,A,Y,X,tempX,N,iterat)
print("\nМетод Якоби:")
print("Решение:")
print(X)
print("Итераций: %d"%iterat[0])
for i in range(N):
    tempX[i]=0
    X[i]=0
iterat[0]=0
func(E,2,A,Y,X,tempX,N,iterat)
print("\nМетод Зейделя:")
print("Решение:")
print(X)
print("Итераций: %d"%iterat[0])

