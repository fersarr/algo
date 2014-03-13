#include <iostream>
using namespace std;

//Rabin-karp string matching. 
//generalizes more easily for 2d pattern matching
//time complexity O(n+m) n=text.length()  m=pattern.length()

int main(){

	string pattern="ababac";
	string text=" ababac hey bacman itsaba fer andababac fersarr ababac to ababac";
	
	int m=pattern.length();
	int n=text.length();
	
	int kBase=27; //26 letters in english alphabet +1 for space. Used to get numeric value of a string. "122" -> 122
	int kMod=997; //big prime number;
	
	int power=1;
	int p_hash=0;
	int t_hash=0;
	
	//compute the hash for the pattern and for the first window (substring of length m) in text string 
	for(int i=0;i<m;i++){
		power=i>0?power*kBase:1; //to get 26^(M-1) -> used when deleting most significant character
		p_hash=(p_hash*kBase+pattern[i])%kMod; //kMod multiplies ALL TERMS (increasing their exponent) in previous hash each time
		t_hash=(t_hash*kBase+text[i])%kMod;
	}

	//try to find the pattern inside the text
	
	for(int i=m;i<n;i++){
		if(p_hash==t_hash ){ //only if they have same hash, compare strings
			if(pattern==text.substr(i-m,m)){
				cout<<"Match found at "<<i-m<<endl;
			}
		}	
		
		
		//Rolling hash technique:
		//remove the Most Significant Char and add a new Least Significant.
		t_hash-=(power*text[i-m])%kMod; //remove MSC
		if(t_hash < 0)
			t_hash+=kMod;
		t_hash=(t_hash*kBase+text[i])%kMod; //add LSC and multiply hash by kBase to increment exponents by one after removing the MSB in previous step
	
	}
	
	//LAST CASE: check if pattern is last substring in text
	if(t_hash == p_hash && text.substr(n-m,m)==pattern)
		cout<<"Match at END "<<n-m<<endl;
	
















	return 0;
}
