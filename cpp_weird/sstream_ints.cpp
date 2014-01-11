#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

int n,opsN;

//states: 31 numbers, 31 possible places to put parenthesis and 6500 different results -2800 to 3000
bool states[31][31][6500];

#define MAX 50
int numbers[MAX];
char ops[MAX];

int main()
{
	string line;

/* 	while(getline(cin,line)){
		stringstream ssline(line);
		
		int c;
		cout<<"LINE "<<line<<endl;
		while(ssline>>c){
			cout<<"C "<<c<<endl;

		}
		cout<<"bla "<<endl;
	} */
	
	char z;
	while(cin>>z)
		cout<<"Z "<<z<<endl;
		
	return 0;
}
