 #include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

// MST minimum spanning tree - Kruskal with UNION-FIND

int n,k,m,oriCost,nodeCount;

//UNION FIND ---------------------------------------------
vector<int> pSet; //parent set. pSet[i] indicates which set i belongs to, using the representative(parent) of that set.

void initSet(int _size) //initialize all sets as having just one element
{
	pSet.resize(_size);
	for(int i=0;i<_size;i++)
		pSet[i]=i;
}

int findSet(int n){
	return pSet[n]==n? n : pSet[n]=findSet(pSet[n]); //recursively to the top for PATH COMPRESSION. 
}

//i will now belong to the set which j belongs to. It is done puting the parent of J'set as the parent of i's set parent.
void unionSet(int i,int j)
{
	pSet[findSet(i)]=findSet(j);
}

bool isSameSet(int i,int j)
{
	return findSet(i)==findSet(j);
}
//UNION FIND-------------------------------------------------


#define MAX 1000010
typedef pair<int, int> pii;
priority_queue<pair<int,pii> > edges;
bool exists[MAX];

int main(){
	
	int n1,n2,cost;
	string blank="";
	while(cin>>n){
		
		memset(exists,0,sizeof(exists));
		cout<<blank;
		blank="\n";
		
		oriCost=0;
		nodeCount=0;
		
		
		//input all edges: node1,node2,cost
		cin>>k;
		for(int i=0;i<k;i++){
			cin>>n1>>n2>>cost;
			edges.push(make_pair(-cost,make_pair(n1,n2))); //negative cost so they are sorted ascending
			if(exists[n1]==false) nodeCount++; exists[n1]=true;
			if(exists[n2]==false) nodeCount++; exists[n2]=true;
			//just in case they are not numbered sequentially 1...N

		}
		
		
		initSet(nodeCount+1); //not zero based
		int newMSTcost=0;
		while(!edges.empty()){ //priority queue is sorted, so first edge has min cost
			pair<int,pii> pair1=edges.top();
			edges.pop();
			cost=pair1.first;
			n1=pair1.second.first;
			n2=pair1.second.second;
			if(!isSameSet(n1,n2)){ //they are not connected
				unionSet(n1,n2);
				newMSTcost+=-cost; // negative because they were already negative for sorting
			}	
		}	
		
		cout<<oriCost<<endl<<newMSTcost<<endl;
		
		
	}













	return 0;
}
