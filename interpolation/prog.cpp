#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
class interpolation
{
	double* x;
	double* y;
	int N;
public:
	void readfile(const char* name_file);
	void readkeyboard();
	void lagrange();
	void newton();
	void show();
};
void interpolation:: readkeyboard()
{
	cout<<"Введите количество точек:";
	cin>>N;
	cout<<endl;
	x=new double[N];
	y=new double[N];
	for(int i=0;i<N;++i){
		cout<<"Введите x["<<i<<"]=";
		cin>>x[i];
		cout<<endl<<"Введите y["<<i<<"]=";
		cin>>y[i];
		cout<<endl;	
	}	
}
void interpolation:: readfile(const char* name_file)
{   
	int i=0;
	N=0;
	double number;
	ifstream fin;
	fin.open(name_file, ios::app);
	if(!fin)
	{
		cout<<"Ошибка при чтении из файла"<<endl;
		exit(1);
	}
	fin>>number;
	N++;
	while(!fin.eof())
	{
		fin>>number;
		N++	;
	}
	N=N/2;
//?	fin.seekg(ios::beg);
	fin.close();
	fin.open(name_file, ios::app);
	x= new double[N];
	y= new double[N];
	fin>>x[i];
	while(!fin.eof())
	{
		fin>>y[i];
		++i;
		fin>>x[i];
	}

	cout<<"end"<<endl;
}
void interpolation:: show()
{
	for(int i=0;i<N;i++)
	{
		cout<<x[i]<<" "<<y[i]<<endl;
	}
}

void interpolation::lagrange()
{
	double X, result=0;
	cout<<"ENTER X  :";
	cin>>X;
	for(int i=0;i<N;i++)
	{	
		double temp=y[i];
		for(int j=0;j<N;j++)
		{
			if(i==j) continue;
			temp*=(X-x[j])/(x[i]-x[j]);
		}
		result+=temp;
	}
	cout<<"Lagrange: "<<result<<endl;
}
void interpolation::newton()
{
	double f[N][N];
	double result=y[0];
	double X;
	cout<<"ENTER X  :";
	cin>>X;
	for(int i=0;i<N;i++)
	{
		f[0][i]=y[i];
	}
	double t =1;
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<N-i;j++)
		{
			f[i][j]=(f[i-1][j+1]-f[i-1][j])/(x[j+i]-x[j]);
		}
		t*= X-x[i-1];
		result+=f[i][0]*t;
	}
	cout<<"Newton: "<<result<<endl;
} 

 int main()
 {
 	interpolation object;
	int n;
	char fn[20];
	cout<<"Нажмите 1 для чтения координат из файла!"<<endl;
	cout<<"Нажмите 2 для чтения координат c клавиатуры!"<<endl;
	cin>>n;
	switch(n){
	case 1: {cout<<"Введите имя файла:";cin>>fn;object.readfile(fn);break;}
	case 2: {object.readkeyboard();break;}
	}
 	object.lagrange();
 	//object.newton();
 	return 0;
 }
