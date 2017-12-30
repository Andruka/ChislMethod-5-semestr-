N=input('N=');
x=0;
d=0;
cur=1;
Max=0;
disp('Ввод матрицы A');
a=input('');   
disp('Ввод матрицы Y');
y=input('');
if(size(a,1)~=N) then
    abort;
    elseif (size(a,2)~=N) then
        abort;
        elseif (size(y)~=N)
            abort;
end
aa=a;
yy=y;
F=zeros(N,1);
z=[a y];
disp('');
disp('Система:');
disp(z);
funcprot(0);
function [ma]=findmax(no,ar,ma,cu)
    ma=cu;
    for i=cu:no
        if abs(ar(ma,cu))<abs(ar(i,cu))
            ma=i;
        end
    end
endfunction
function [ar,Y]=swap(cu,ma,ar,Y,no)
    if(ma ~= cu)
        for i=cu:no
            te=ar(ma,i);
            ar(ma,i)=ar(cu,i);
            ar(cu,i)=te;
        end
    te=Y(ma);
    Y(ma)=Y(cu);
    Y(cu)=te;
    end
    te=ar(cu,cu);
    for i=cu:no
        for j=cu:no
            ar(i,j)=ar(i,j)/te;
        end
        Y(i)=Y(i)/te;
    end
endfunction
function [ar,Y]=func1(ar,Y,cu,no)
    for i=cu+1:no
        temp=ar(i,cu);
        for j=cu:no
            ar(i,j)=ar(i,j)-ar(cu,j)*temp;
        end
        Y(i)=Y(i)-Y(cu)*temp;
    end
endfunction
function [ar,Y]=gauss1(ar,Y,cu,no)
    for cu=1:no-1
        [Max]=findmax(no,ar,Max,cu);
        [ar,Y]=swap(cu,Max,ar,Y,no)
        [ar,Y]=func1(ar,Y,cu,no);
    end
endfunction
function [ar,Y,X]=func2(ar,Y,cu,no,X)
    Y1=Y(cu);
    if no~=cu
        for i=no:-1:cu
            Y1=Y1-ar(cu,i)*X(i);
        end
    end
    X(cu)=Y1/ar(cu,cu);
endfunction
function [ar,Y,X]=gauss2(ar,Y,cu,no,X)
    for cu=no:-1:1
        [ar,Y,X]=func2(ar,Y,cu,no,X);
    end
endfunction
function [f]=calcVect(f,ar,Y,no,X)
    for i=1:no
        for j=1:no
            f(i)=f(i)+ar(i,j)*X(j);
        end
        disp(f(i));
        f(i)=f(i)-Y(i);
        disp(f(i));
    end
endfunction
function [d]=findnorm(d,F,N)
    d=abs(F(1));
    for i=1:N
        if(d<abs(F(i)))
            d=abs(F(i));
        end
    end
endfunction    
[a,y]=gauss1(a,y,cur,N);
z=[a y];
[a,y,x]=gauss2(a,y,cur,N,x);
[F]=calcVect(F,aa,yy,N,x);
[d]=findnorm(d,F,N);
disp('');
disp('Решение:');
disp(x);
disp("Вектор невязки: F=AX*-b:");
disp(F);
disp("Норма:");
disp(d);


