#include <iostream>
#include <cmath>
using namespace std;

/*
Bisection method
before, we used binary search for finding items in a static sorted array.
However, the binary search principle can also be used to find the root of
a function that may be difficult to compute mathematically.

The method is applicable when we wish to solve the equation f(x) = 0 for the real variable x,
 where f is a continuous function defined on an interval [a, b] and f(a) and f(b) have
  opposite signs.


UVa problems
10341(Solve It)
358(Don't Have a Cow, Dude). 
10297(Beavergnaw),
Railway (10263)
*/

float f(float x){
	return x*x-2;
}


int main()
{

	//interval [a-b]
	float a=1.0,b=2.0,tol=0.01,x,pos,neg, avg,f_avg;
	
	if(f(a)>f(b)) {
		pos=a;
		neg=b;
	}
	else{
		pos=b;
		neg=a;
	}
	
	avg=pos;
	while(abs(f(avg)-0.0)>tol){
		avg=(pos+neg)/2.0;
		f_avg=f(avg);
		cout<<"iter "<<neg<<"\t-\t"<<pos<<"\t f(avg)="<<f(avg)<<endl;
		if(f_avg>0.0)
			pos=avg;
		else
			neg=avg;
	}
	
	cout<<"Root : f("<<avg<<")= "<<f(avg)<<endl;



	return 0;
}
