#include <iostream>
using namespace std;

//KMP string matching

//KMP string matching time O(m+n) N=TEXT.LENGTH() and m is patterns length
//preprocessing (fail function) takes at most 2*length(pattern)
//algorithm: 2*length(text) - length(pattern) - 1
//thus the overall complexity is O(m+n) and no more m + 2*n 


//find the pattern in the text

#define TESTS 6
string patterns[TESTS]={"fer",
						"fer",
						"fer",
						"fer",
						"car",
						"yiyo"
						};
string texts[TESTS]={"holasoyfersarr",
					"fer",
					"f",
					"feta",
					"tomacar",
					"yiyo,mi nombre es yiyo",
					};


#define MAX 1000
int fail[MAX]; //0 to m (total length: lengthofpattern+1



int main()
{
	int tests=TESTS;
	
	int matched=0;
	
	string pattern,text;
	
	for(int k=0;k<tests;k++){
	
		cout<<"KMP search"<<endl;
		pattern=patterns[k];
		text=texts[k];
		
		//build FAIL function - find longest proper suffix that's also a prefix.
		//its like searching for the pattern inside the pattern
		
		fail[0]=0;
		fail[1]=0;
		int j; // j is the index of the largest next partial match (the largest suffix/prefix) of the string under index i-1
		for(int i=2;i<pattern.length();i++){
			j=fail[i-1]; //first time is zero. gets the fail[i] value from the previous iteration
			while(1){ //only does more than 1 iteration if no match but there are other possible candidates
				if(pattern[j]==pattern[i-1]){
					fail[i]=j+1; //j will later become this value from f[i-1] (increase j and i) 
					break;
				}
				else if (j==0){ //can't go further
					fail[i]=0;
					break;
				}
				j=fail[j]; //try next best partial match
			}
		}
		
		//now kmp search
		int i=0;
		j=0;
		bool found=false;
		
		while(1){
			if(i==text.length()) //end of text
				break;
			if(pattern[j]==text[i]){
				i++;
				j++;
				if(j==pattern.length()){
					cout<<"\tMatch at "<<i-pattern.length()<<endl;
					j=0;
					found=true;
				}
			}
			else if (j>0) //next partial match  
				j=fail[j];
			else	//we had only reached the empty string and failed to expand, next in text
				i++; 
		
		}
		
		if(!found)
			cout<<"\tNo Match"<<endl;
		
	
	
	
	}
	
	
	
	











	return 0;

}
