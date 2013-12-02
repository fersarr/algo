#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*Segment Tree:  tree data structure for storing intervals, or segments
Efficiently answers dynamic range queries in array A. Convenient if A is frequently updated.if static, use DP
stores intervals, and optimized for "which of these intervals contains a given point" queries.
queries like:
-Minimum element in an array
-Maximum
-SUM

Performance / Space consumption for one dimension:
Segment tree - O(n logn) preprocessing time, O(k+logn) query time, O(n logn) space
interval can be added/deleted in O(logn) time

No node has only one son! all have two or zero (leaf)

*/ 

#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2

vector<int> segTree;
void init_segTree(int code,int N)
{
	//the tree is going to have more nodes than needed. But the unused nodes won't have a problem and won't need initialization
	//because they won't be accessed. For example, query will stop when the query interval is outside all possible intervals
	int nodes=(int)  (2*pow(2.0,   floor ((log   ((double)N) / log (2.0))) +1 )); //2*2^ ( floor(log2(N))  +1)
	segTree.resize(nodes);
	
}

//code indicates if we want min,max or sum. 
//a is the array to be transformed into segTree
//node is the current node inside the segtree
//a & b are the left and right boundaries of the segment
void build_segTree(int code,int A[],int node, int a,int b)
{
	//base case
	if(a==b){ //equal, use any. 
		if(code==RANGE_SUM) segTree[node]=A[a]; //store value
		else				segTree[node]=a;	//store index
	}
	//left & right subtrees
	else{ 
		int leftId=2*node,rightId=2*node+1;
		int avg=(a+b)/2;
		build_segTree(code,A,leftId ,a    ,avg); //left
		build_segTree(code,A,rightId,avg+1,b);   //right
		int leftContent=segTree[leftId];
		int rightContent=segTree[rightId];
		
		if(code==RANGE_SUM){ //the segment contains sum of left & right subtree
			segTree[node]=leftContent+rightContent;
		}
		else{ //min and max
			int leftValue =A[leftContent];
			int rightValue=A[rightContent];
			if(code==RANGE_MIN)		segTree[node]=(leftValue<=rightValue?leftContent:rightContent); //MIN
			else					segTree[node]=(leftValue>=rightValue?leftContent:rightContent); //MAX
		}
	}
}

//a-b current interval ---- i-j query interval
int query(int code, int A[],int node,int a,int b,int i,int j){
	//cout<<"query "<<a<<"-"<<b<<endl;
	if (b<i || a>j) {
		cout<<"outside, discard "<<a<<","<<b<<endl;
		return -1; //current interval doesn't intersect query interval
	}
	if (a>=i && b<= j){ //[a-b] is inside [i-j] return the segment value
		cout<<"inside ret"<<node<<": "<<segTree[node]<<endl;
		return segTree[node]; //current inter inside query interval, give the value
	}
	
	//compute minimum position in left & right part of interval
	int p1=query(code,A,2*node  ,a        ,(a+b)/2  ,i,j);
	int p2=query(code,A,2*node+1,(a+b)/2+1,b        ,i,j);
	
	//if one son returns -1, use the other. it has to be used because parent segment wasnt outside
	//return position of the overall minimum
	if (p1==-1) return p2; //when  we try to access segment outside query
	if (p2==-1) return p1;
	
	//if both sons are inside, consider both answers
	if      (code==RANGE_SUM) 	return p1+p2;
	else if (code==RANGE_MIN)	return (A[p1] <= A[p2]) ? p1:p2;
	else   						return (A[p1] >= A[p2]) ? p1:p2;
}

void update(int code,int A[], int node,int a,int b,int updateIndex,int updateValue)
{
	if(a==updateIndex && b==updateIndex){  //REACHED THE NODE. UPDATE (FIRST IF EQUAL)
		cout<<"modify "<<a<<" "<<b<<endl;
		if(code==RANGE_SUM) segTree[node]=updateValue;
		else 				segTree[node]=updateIndex;
		A[updateIndex]=updateValue;
	}
	else{
		if(a<=updateIndex && updateIndex<=b){ //its inside, go to sons (SECOND IF CONTAINED)
			cout<<"check sons of "<<a<<" "<<b<<endl;
			update(code,A,2*node   ,a          ,(a+b)/2  ,updateIndex,updateValue);
			update(code,A,2*node+1 ,(a+b)/2+1  ,b        ,updateIndex,updateValue);
		}
		else if (updateIndex<a || updateIndex>b){ //wrong branch, discard, prune
			cout<<"discard "<<a<<" "<<b<<endl;
			return;
		}
	
		//update parent segments based on new value
		if      (code==RANGE_SUM) 	{segTree[node]=segTree[2*node]+segTree[2*node+1];
			cout<<"updateParentSUM: "<<node<<"= "<<segTree[node]<<endl;
		}
		else if (code==RANGE_MIN)	segTree[node]=((updateValue < A[segTree[node]]) ? updateIndex : segTree[node]);
		else   						{segTree[node]=((updateValue > A[segTree[node]]) ? updateIndex : segTree[node]);
			cout<<"updateParentMAX: "<<node<<"= "<<((updateValue > A[segTree[node]]) ? updateIndex : segTree[node])<<endl;
		}  //MAX
	}
}

bool isPowerOfTwo(int x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}


void printSegTree(int code, int A[], int N)
{
	int numberOfNodes=(int)  (2*pow(2.0,   floor ((log   ((double)N) / log (2.0))) +1 ));
	cout<<endl<<"SegTree "<<endl;
	
	for(int i=1;i<=numberOfNodes;i++){
		if(isPowerOfTwo(i)){
			cout<<endl;
		}
		if (code== RANGE_SUM) cout<<segTree[i]<<" ";
		else cout<<A[segTree[i]]<<" ";
	}
	cout<<endl<<endl;
}




int main()
{
	int A[]={8,7,3,9,5,1,10}; 
	int _size=sizeof(A)/sizeof(int);
	
	int code=RANGE_SUM;
	
	init_segTree(code,_size);
	build_segTree(code,A,1,0,6);

	printSegTree(code,A,_size);
	cout<<"MAX QUERY: *** "<<query(code,A,1,0,6,1,3)<<endl<<endl; //answer should be index 2m
	
	cout<<"UPDATE ---------------- "<<endl;
	update(code,A,1,0,6,1,99);
	
	printSegTree(code,A,_size);
	cout<<"MAX QUERY: *** "<<query(code,A,1,0,6,1,3)<<endl<<endl; //answer should be index 1
	









	return 0;
}
