#include"gauss.h"

int main(){
	int check=0;
	float time=0;
	float time2=0;
	Gauss ob;
	while(check!=1&&check!=2){
		cout<<"Нажмите 1, если хотите ввести уравнения в ручную!"<<endl<<"Нажмите 2, если хотите загрузить уравнения из файла!"<<endl;
		cin>>check;
		if(check==1){
			ob.readkeyboard();
			}
		if(check==2){
			ob.readfile();
			}
		}
	ob.showMatrix();
	time=clock();
	ob.gauss1();
	time2=clock();
	time2-=time;
	cout<<"Время работы прямого хода: "<<time2/1000<<" сек."<<endl;
	time2=clock();
	ob.gauss2();
	time=clock();
	time-=time2;
	cout<<"Время работы обратного хода хода: "<<time/1000<<" сек."<<endl;
	ob.showResult();
	ob.calcvector();
	ob.showVector();
	}
