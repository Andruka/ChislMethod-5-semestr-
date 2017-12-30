x = -%pi*5:0.1:%pi*5; 
xlabel('X [ ]');
ylabel('Y [ ]');
title('Разложение sin в ряд Тейлора')
xset("thickness",3);
y = sin(x);
y1=x;
y2=x-(x.^3)/6;
y3=x-(x.^3)/6+(x.^5)/factorial(5);
y4=x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7);
y5=x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7)+(x.^9)/factorial(9);
y6=x-(x.^3)/6+(x.^5)/factorial(5)-(x.^7)/factorial(7)+(x.^9)/factorial(9)-(x.^11)/factorial(11);
plot2d(x,y,style=[color("black")],rect=[-16,-4, 16,4]);
plot2d(x,y1,style=[color("green")],rect=[-16,-4, 16,4]);
plot2d(x,y2,style=[color("pink")],rect=[-16,-4, 16,4]);
plot2d(x,y3,style=[color("yellow")],rect=[-16,-4, 16,4]);
plot2d(x,y4,style=[color("blue")],rect=[-16,-4, 16,4]);
plot2d(x,y5,style=[color("orange")],rect=[-16,-4, 16,4]);
plot2d(x,y6,style=[color("red")],rect=[-16,-4, 16,4]);
legend('sin (x)','x','x-(x^3)/3!','x-((x^3)/3!)+((x^5)/5!)','x-((x^3)/3!)+((x^5)/5!)-((x^7)/7!)',"x-(x^3)/6+(x^5)/5!-(x^7)/7!+(x^9)/9!","x-(x^3)/6+(x^5)/5!-(x^7)/7!+(x^9)/9!-(x^11)/11!");
xset("thickness",1);
xgrid();
