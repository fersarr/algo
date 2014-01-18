#include <iostream>
#include <stack>
using namespace std;

//Min Edit distance using Levenshtein costs (2 for substitution and 1 for insertion and deletion)

#define MAX 1000
int states[MAX][MAX];

int main(){
	//string s1="informatics";
	//string s2="bioinformatics";
	
	//string s1="oferta";
	//string s2="chofer";
	
	//string s1="intention";
	//string s2="execution";
	
	//string s1="saturday";
	//string s2="sunday";
	
	string s1="abcde";
	string s2="bcgfe";
	
	int m=s1.length();
	int n=s2.length();
	
	cout<<endl;
	cout<<"s1: "<<s1<<"\t size: "<<m<<endl;
	cout<<"s2: "<<s2<<"\t size: "<<n<<endl;
	//DP bottom UP
	// deﬁne states[i][j] is the edit distance between s1[1..i] and s2[1..j]
	
	//base cases
	for(int i=0;i<=m;i++)
		states[i][0]=i;
	for(int i=0;i<=n;i++)
		states[0][i]=i;
	
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			//deletions are done to s2 (one deletion to s1 == one insertion to s2 )
			int insertion=states[i-1][j]+1;
			int deletion=states[i][j-1]+1;
			states[i][j]=min(insertion,deletion);
			if(s1[i-1]==s2[j-1]){ //match, strings are zero-indexed
				states[i][j]=min(states[i][j],states[i-1][j-1]+0);
			}
			else //substitution
				states[i][j]=min(states[i][j],states[i-1][j-1]+2);
		}
	}

	cout<<endl;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			cout<<states[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	cout<<"Min Edit Distance "<<states[m][n]<<endl;

	cout<<"Alignment --- "<<endl;
	
	int i=m,j=n ,i2,j2 ,minSoFar,action=0; 
	stack<int> actions;
	
	bool go=true;
	while(go){// && !(i==0 && j==0)){
		//cout<<"i,j = "<<i<<","<<j<<endl;
		go=false;
		minSoFar=states[i][j];
		
		//insertion in s2
		if(i>0){
			minSoFar=states[i-1][j];
			i2=i-1;
			j2=j;
			action=1;
			go=true;
		}
		//deletion
		if(states[i][j-1]<minSoFar && j>0){
			minSoFar=states[i][j-1];
			i2=i;
			j2=j-1;
			action=2;
			go=true;
		}
		//match or substitution
		if(states[i-1][j-1]<minSoFar && j>0 && i>0){
			minSoFar=states[i-1][j-1];
			i2=i-1;
			j2=j-1;
			action=3;
			//substitution
			if(states[i-1][j-1]!=states[i][j])
				action=4;
			go=true;
		}
		
		if(go)
			actions.push(action);
		i=i2;
		j=j2;
	}
	
	int alignedSize=actions.size();
	string s1edited(alignedSize,'0');
	string s2edited(alignedSize,'0');
	
	int index=0,s1index=0,s2index=0;
	while(!actions.empty()){
		action=actions.top();
		actions.pop();
		if(action==1){      //insert in s2
			s1edited[index]=s1[s1index++];
			s2edited[index]='_';
		}
		else if(action==2){ //insert in s1
			s1edited[index]='_';
			s2edited[index]=s2[s2index++];
		}
		else if(action==3){ //match
			s1edited[index]=s1[s1index++];
			s2edited[index]=s2[s2index++];
		}
		else if(action==4){ //substitution
			s1edited[index]=s1[s1index++];
			s2edited[index]=s1edited[index];
			s2index++;
		}
		index++;
	}
	
	cout<<"s1edited: "<<s1edited<<endl;
	cout<<"s2edited: "<<s2edited<<endl;
	

	return 0;
}





























