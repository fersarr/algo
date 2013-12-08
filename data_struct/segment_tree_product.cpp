#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;


/*

4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
*/

//This problem requires dynamic quering for intervals inside a static array that can be updated. Therefore, SEGMENT TREE.
//In this case, the segTree is built for interval product.

#define MAX 100010
int A[MAX];
char answer[MAX];

vector<int> segTree;

void init_segTree(int N)
{
	int _size=2*pow(2,  floor(log(N)/log(2))+1  );
	//cout<<"size "<<_size<<endl;
	segTree.resize(_size);
}

//fill in the nodes
int build_segTree(int A[],int node,int a,int b){
	
	if(a==b) //base case
		return segTree[node]=A[a]; //store the value of the array
	int avg=(a+b)/2;
	int left=build_segTree(A,2*node,a,avg); 		//left son
	int right=build_segTree(A,2*node+1,avg+1,b);	//right son
	
	return segTree[node]=left*right;
}


//i-j is the query interval (inclusive)
int query(int A[],int node,int a,int b,int i,int j)
{
	//cout<<"IN "<<a<<","<<b<<endl;
	if (j<a || i >b){ //query interval is outside of this segment, discard
		//cout<<"discard "<<a<<","<<b<<endl;
		return 1; //neutral element of multiplication
	}
	else if( a>=i && b<=j){ //[a-b] is inside [i-j] return the segment value
		//cout<<"\t"<<segTree[node]<<endl;
		return segTree[node];
	}
	else{
		int avg=(a+b)/2;	
		int left=query (A,2*node  ,a      ,avg,i,j);
		int right=query(A,2*node+1,avg+1  ,b  ,i,j);
		//cout<<"\t"<<"L,R   "<<left<<","<<right<<endl;
		return right*left; //combine unusual branches	 
	}
}

void update(int A[],int node,int a,int b,int updateIndex,int updateValue)
{
	if (updateIndex<a || b <updateIndex){ //wrong branch, discard ///VER DE EVITAR ESTO SOLO LLAMANDO A UPDATE EN LA RAMA CORRECTA
		//cout<<"discard "<<a<<","<<b<<endl;
		return ;
	}
	else if(a==b && a==updateIndex){ //reached, update
		A[updateIndex]=updateValue;
		segTree[node]=updateValue;
	}
	else{ //updateIndex is inside [a-b], go to sons 
		int avg=(a+b)/2;	
		update(A,2*node  ,a      ,avg,updateIndex,updateValue);
		update(A,2*node+1,avg+1  ,b  ,updateIndex,updateValue);
		segTree[node]=segTree[2*node]*segTree[2*node+1];
		//cout<<"\t"<<segTree[2*node]*segTree[2*node+1]<<endl;
	}

}

int main()
{
	int n,k;
	memset(answer,'_',MAX);
	while(cin>>n>>k){
		segTree.clear();
		int _size=n;
		int maxIndex=_size-1;
		int pos=0; //position in answer string
		
		for(int i=0;i<n;i++){
			int num;
			cin>>num;
			if    	(num>0) A[i]=1;
			else if	(num<0) A[i]=-1;
			else			A[i]=0;
		}
		
		init_segTree(_size);
		build_segTree(A,1,0,maxIndex);
		
		//cout<<"COMMANDS --- "<<endl;
		char c;
		int i,j,ans;
		for(int q=0;q<k;q++){
			cin>>c>>i>>j;
			i=i-1;
			if(c=='C'){
				//cout<<"update --- "<<i<<" "<<j<<endl;
				if(j>0) 	 j=1;
				else if(j<0) j=-1;
				else 		 j=0;
				update(A,1,0,maxIndex,i,j);
			}
			else{
				j=j-1; //j is index too
				if (pos) pos--; //erase (overwrite) the \0 (NULL) from last product command
				ans=query(A,1,0,maxIndex,i,j);
				if(ans==0)		cout<<'0';
				else if(ans>0)	cout<<'+';
				else 			cout<<'-';
				//cout<<"ans "<<ans<<" in answer[] "<<pos<<"="<<answer[pos-2]<<endl;
			}	
			
		}
		
		cout<<endl;
		
		
	}

	return 0;
}




/*
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5

*/












