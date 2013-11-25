#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

/*
Strongly Connected Components of a Undirected Graph.
-v & w are SCC if there's a path from v to w and from w to v.

Kosaraju Algorithm (DOUBLE PASS DFS, linear time E+V):
inverse graph G -> R
dfs to obtain reversed post order of R
dfs G in the order given by reverse post order of R and mark in an array (array[nodeid]=SCC_id) the SCC id as we visit each node


*/

#define MAX 13

typedef vector<int> vi;
typedef vector<vi > vvi;

int visited[MAX]={0};
int visited2[MAX]={0};
int SCCids[MAX]={0};
stack<int> postOrder;

vvi graphG,graphR; //original and reversed graph

void dfs(int node){
	visited[node]=true;
	vi newVec = graphR[node];	
	vi::iterator it;
	for(it=newVec.begin();it!=newVec.end();it++){
		int son=*it;
		if(visited[son]==false){
			dfs(son);
		}
	}
	postOrder.push(node);
}

void dfs_mark(int node, int SCCid){ //mark with SCC id
	visited2[node]=true;
	SCCids[node]=SCCid;
	vi newVec = graphG[node];	
	vi::iterator it;
	for(it=newVec.begin();it!=newVec.end();it++){
		int son=*it;
		if(visited2[son]==false){
			dfs_mark(son,SCCid);
		}
	}
}

int main()
{
	ifstream fin ("graph1.txt");
	
	for(int i=0;i<MAX;i++){
		vi newVecG,newVecR;
		graphG.push_back(newVecG);
		graphR.push_back(newVecR);
	}
	
	
	int node1,node2;
	while(fin>>node1>>node2){
		//cout<<node1<<" "<<node2<<endl;
		graphG[node1].push_back(node2);
		graphR[node2].push_back(node1);
	}
	
	
	for(int i=0;i<MAX;i++){
		if(visited[i]==false){
			dfs(i);
		}
	}	
	
	cout<<"Reversed PostOrder of R"<<endl;
	int SCCid=0;
	while(!postOrder.empty()){
		int node=postOrder.top();
		postOrder.pop();
		//cout<<node<<endl;
		if(visited2[node]==false){
			dfs_mark(node,SCCid);
			SCCid++;
		}
	}
	
	
	cout<<"Node\tSCCid"<<endl;
	for(int i=0;i<MAX;i++){
		cout<<i<<"\t"<<SCCids[i]<<endl;
	}
	

	return 0;
}

