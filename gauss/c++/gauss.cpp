#include"gauss.h"

Gauss::Gauss(){
	n=0;//количество уравнений
	cur=0;//текущая строка или столюец, взависимости от ситуации
	max=0;//номер строки с максимальным элементом в нужном нам столбце
	}
void Gauss::readkeyboard(){//чтение с клавиатуры
	cout<<"Введите размер матрицы (n):"<<endl;
	cin>>n;
	A=new float *[n+1];//массив коэффициентов
	for(int i=0;i<n+1;++i)A[i]=new float[n+1];
	Y=new float[n+1]; //вектор, то есть правая часть уравнения
	X=new float[n+1]; //вектор иксов, то есть решений
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<"Введите a["<<i<<"]["<<j<<"]:"<<endl;
			cin>>A[i][j];
			}
		cout<<"Введите y"<<i<<endl;
		cin>>Y[i];
		}
	A1=new float *[n+1];//сохраняем матрицу коэффициентов для рассчёта вектора невязки
	for(int i=0;i<n+1;++i)A1[i]=new float[n+1];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)A1[i][j]=A[i][j];
		}
	Y1=new float[n+1];//сохраняем вектор b для векторора невязки
	for(int i=0;i<n;++i)Y1[i]=Y[i];
	F=new float[n+1];//создаём вектор невязки
	for(int i=0;i<n;++i)F[i]=0;
	}
void Gauss::readfile(){//чтение из файла
	char *fn=new char[20];//имя файла
	ifstream fin;
	char ch=0;//просто символьная переменная в которую считываем из файла,нужна,чтобы подсчитать количество уравнений
	int num=0;//количество пробелов в первой строке
	cout<<"Введите имя файла:"<<endl;
	cin>>fn;
	fin.open(fn);
	while(ch!=10){
		fin.read((char*)&ch,1);
		if(ch==32)++num;
		}
	n=num;
	cur=0;
	max=0;
	fin.seekg(0);
	X=new float [n+1];
	Y=new float [n+1];
	A=new float *[n+1];
	for(int i=0;i<n+1;++i)A[i]=new float[n+1];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)fin>>A[i][j];
		fin>>Y[i];
		}
	A1=new float *[n+1];
	for(int i=0;i<n+1;++i)A1[i]=new float[n+1];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)A1[i][j]=A[i][j];
		}
	Y1=new float[n+1];
	for(int i=0;i<n;++i)Y1[i]=Y[i];
	F=new float [n+1];
	for(int i=0;i<n;++i)F[i]=0;
	}
void Gauss::findMax(){//поиск главного элемента
	max=cur;
	for(int i=cur;i<n;++i){
		if(fabs(A[max][cur])<fabs(A[i][cur]))max=i;
		}
	}
void Gauss::swap(){//перестановка строк
	float temp;//пустой флоат,нужен для обмена значений между переменными
	findMax();
	if(cur!=max){
		for(int i=cur;i<n;++i){
			temp=A[max][i];
			A[max][i]=A[cur][i];
			A[cur][i]=temp;
			}
		temp=Y[max];
		Y[max]=Y[cur];
		Y[cur]=temp;		
		}
	temp=A[cur][cur];
	for(int i=cur;i<n;++i){
		for(int j=cur;j<n;++j){
			A[i][j]/=temp;
			}
		Y[i]/=temp;
		}
	}
void Gauss::func(){
	float temp;//пустой флоат, нужен для приведения матрицы к векхнетреугольному виду
	for(int j=1;cur+j<n;++j){
		temp=A[cur+j][cur];
		for(int i=cur;i<n;++i){
			A[cur+j][i]-=A[cur][i]*temp;
			}
		Y[cur+j]-=Y[cur]*temp;
		}
	}
void Gauss::gauss1(){//прямой ход Гаусса
	for(;cur<n-1;++cur){
		swap();
		func();
		}
	}
void Gauss::func2(){
	float Y1=Y[cur];
	if(n!=cur){
		for(int i=n-1;i>cur;--i){
			Y1-=A[cur][i]*X[i];
			}
		}
	X[cur]=Y1/A[cur][cur];
	}
void Gauss::gauss2(){//обратный ход Гаусса
	for(;cur>=0;--cur){
		func2();
		}
	}
void Gauss::showMatrix(){
	cout<<endl<<"СЛАУ:"<<endl;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cout<<A[i][j]<<"*X"<<j+1<<"  ";
			}
		cout<<"  =  "<<Y[i]<<endl;
		}
	}
void Gauss::showResult(){
	cout<<endl<<"Result:"<<endl;
	for(int i=0;i<n;++i){
		cout<<"X"<<i+1<<" = "<<X[i]<<endl;
		}
	}
void Gauss::calcvector(){//подсчёт вектора невязки
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			F[i]+=A1[i][j]*X[j];
			}
		F[i]-=Y1[i];
		}
	}
void Gauss::showVector(){
	float norma=F[0];//норма вектора невязки
	for(int i=0;i<n;++i){
		cout<<"F["<<i<<"]="<<F[i]<<endl;
		if(fabs(norma)<fabs(F[i]))norma=fabs(F[i]);
		}
	cout<<"Норма="<<norma<<endl;
	}
