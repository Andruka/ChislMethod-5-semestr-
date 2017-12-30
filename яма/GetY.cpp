#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstring>
#include <cctype>
using namespace std;

int initial(char *fn,vector<float> &grafic){
	ifstream in(fn);
	if(!in)return 1;
	float Y1=0,Y2=0,Ymiddle;
	for(int i=0;i<252;i+=2){
		if(i==0){
			in>>Y1;
			grafic.push_back(Y1);
			continue;
			}
		in>>Y2;
		if(in.eof())break;
		Ymiddle=(Y1+Y2)/2;
		grafic.push_back(Ymiddle);
		grafic.push_back(Y2);
		Y1=Y2;
		}
	in.close();
	return 0;
	}
float calculationY(vector<float>grafic,float X){
	float X1=0,X2=0,Y1=0,Y2=0;
	float Y=0;
	X1=(int)X;
	X2=(int)X+1;
	Y1=grafic[X1];
	Y2=grafic[X2];
	Y=X*((Y2-Y1)/(X2-X1))+((X2*Y1-X1*Y2)/(X2-X1));
	return Y;
	}
int getY(vector<float>grafic){
	float X=0;
	while(1){
		cout<<endl<<"Введите значение X, чтобы получить соответвствующее ему значение Y!"<<endl<<"Введите -1, чтобы выйти"<<endl<<"X=";
		cin>>X;
		if(X==-1)return -1;
		if((X<0 && X!=-1)||X>((grafic.size()-1)))return 1;
		cout<<"Y="<<calculationY(grafic,X)<<endl;
		}
	}
int main(){
	char fileName[15];
	vector<float>grafic;
	cout<<"Input file name for initialization:"<<endl;
	while(1){
		cin>>fileName;
		system("clear");
		if(!initial(fileName,grafic)){
			cout<<"Initialization successful!"<<endl;
			break;
			}
		cout<<"File not found!Try again..."<<endl;
		}
	while(1){
	 	if(getY(grafic)!=1)return 0;
		}
	}
