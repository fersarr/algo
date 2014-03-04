#include <iostream>
using namespace std;

//find the pattern in the text

#define TESTS 5
string patterns[TESTS]={"fer",
						"fer",
						"fer",
						"fer",
						"car"
						};
string texts[TESTS]={"holasoyfersarr",
					"fer",
					"f",
					"feta",
					"tomacar"
					};


int main()
{
	int tests=TESTS;
	
	int matched=0;
	bool found=false;
	
	string pattern,text;
	for(int k=0;k<tests;k++){
		found=false;
		pattern=patterns[k];
		text=texts[k];
		for(int i=0;i<text.length();i++){
			matched=0;
			for(int j=0;j<pattern.length();j++){
				if(pattern[j]!=text[i+j])
					break;
				if(j==pattern.length()-1){
					cout<<"Match at "<<i<<endl;
					found=true;
				}
			}
		}
		
		if(found==false)
			cout<<"No match"<<endl;
	
	
	}

	











	return 0;

}
