#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include "myGraphLibs.h"
using namespace std;

/*topological sort ( only for DAG ): 
Using DFS with recursion
1) dfs. when there is no more to explore from one node, push it to postOrder stack. 
2)return reversed postOrder

*/

#define MAX 7
typedef vector<int> vi;
typedef vector<vi > vvi;

bool visited[MAX]={0};
vvi graph;

stack<int> postOrder;

void dfs(int node)
{
	visited[node]=true;
	vi newVec;
	vi::iterator it;
	newVec=graph[node]; //vector of neighboors
	for(it=newVec.begin();it!=newVec.end();it++){
		int son=*it;
		if(visited[son]==false){
		    dfs(son);
		}
	}
	postOrder.push(node);
	return;
}

int main(){
	char fileName[]="dag1.txt";
	graph=readGraph(fileName);

	for(int i=0;i<MAX;i++){
		if(visited[i]==false){
			dfs(i);
		}
	}
	
	cout<<"Reversed post Order"<<endl;	
	while(!postOrder.empty()){
		cout<<postOrder.top()<<endl;
		postOrder.pop();
	}
	

	return 0;
}










