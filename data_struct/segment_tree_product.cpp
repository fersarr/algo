#include <iostream>
#include <vector>
#include <cmath>
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

vector<int> segTree;

void init_segTree(int N)
{
	int _size=2*pow(2,  floor(log(N)/log(2))+1  );
	cout<<"size "<<_size<<endl;
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
	if (j<a || i >b){ //query interval is outside of array
		//cout<<"discard "<<a<<","<<b<<endl;
		return -1;
	}
	else if( a>=i && b<=j) //[a-b] is inside [i-j] return the segment value
		return segTree[node];
	else{
		int avg=(a+b)/2;	
		int left=query (A,2*node  ,a      ,avg,i,j);
		int right=query(A,2*node+1,avg+1  ,b  ,i,j);
		//cout<<"\t"<<"L,R   "<<left<<","<<right<<endl;
		if      (left  == -1) return right;
		else if (right == -1) return left;
		else				  return right*left; //combine unusual branches	 
	}
}

void update(int A[],int node,int a,int b,int updateIndex,int updateValue)
{
	if (updateIndex<a || b <updateIndex){ //wrong branch, discard
		//cout<<"discard "<<a<<","<<b<<endl;
		return ;
	}
	else if(a==b && a==updateIndex){ //reached, update
		A[updateIndex]=updateValue;
		segTree[node]=updateValue;
	}
	else if(a<=updateIndex && updateIndex<=b){ //its inside, go to sons {
		int avg=(a+b)/2;	
		update(A,2*node  ,a      ,avg,updateIndex,updateValue);
		update(A,2*node+1,avg+1  ,b  ,updateIndex,updateValue);
		segTree[node]=segTree[2*node]*segTree[2*node+1];
	}

}

int main()
{

	segTree.clear();
	int A[]={1,2,3,4,5,6,7};
	int _size=sizeof(A)/sizeof(int);
	int maxIndex=_size-1;
	init_segTree(_size);
	build_segTree(A,1,0,maxIndex);

	cout<<"QUERY "<<query(A,1,0,maxIndex,0,3)<<endl<<endl;
	cout<<"QUERY "<<query(A,1,0,maxIndex,1,3)<<endl<<endl;
	cout<<"QUERY "<<query(A,1,0,maxIndex,2,5)<<endl<<endl;
	cout<<"QUERY "<<query(A,1,0,maxIndex,0,6)<<endl<<endl;
	
	update(A,1,0,6,0,0);
	
	cout<<"QUERY "<<query(A,1,0,maxIndex,0,3)<<endl<<endl;
	cout<<"QUERY "<<query(A,1,0,maxIndex,1,3)<<endl<<endl;
	
	update(A,1,0,6,0,1);
	cout<<"QUERY "<<query(A,1,0,maxIndex,0,6)<<endl<<endl;
	
	update(A,1,0,6,3,1000); //instead of 4 we put 1000 -> 5040/4=1260 -> *1000 -> 1260000
	cout<<"QUERY "<<query(A,1,0,maxIndex,0,6)<<endl<<endl;
	
	/* output
	QUERY 24

QUERY 24

QUERY 360

QUERY 5040

QUERY 0

QUERY 24

QUERY 5040

QUERY 1260000

*/

	return 0;
}
