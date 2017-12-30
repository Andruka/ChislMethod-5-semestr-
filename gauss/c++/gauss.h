#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<ctime>

using namespace std;

class Gauss{
	float **A,**A1,*Y,*Y1,*F,*X;
	int n,max,cur;
    public:
	Gauss();
	void readfile();
	void readkeyboard();
	void findMax();
	void swap();
	void func();
	void gauss1();
	void func2();
	void gauss2();
	void showMatrix();
	void showResult();
	void calcvector();
	void showVector();
};
