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

DFS without recursion
http://stackoverflow.com/questions/20153488/topological-sort-using-dfs-without-recursion#20153735

In order to construct the postOrder list you need to know the time when your algorithm has finished 
processing the last child of node k.

change the type of your dfs stack to vector<pair<bool,int> >. 
When the bool is set to true, it indicates a parent; false indicates a child.

When you pop a "child pair" (i.e. one with the first member of the pair set to false) off the stack, 
you run the code that you currently have, i.e. push all their children onto the stack with your for loop. 
Before entering the for loop, however, you should push make_pair(true, node) onto the stack to mark the
 beginning of all children of this node.

When you pop a "parent pair" off the stack, you push the parent index onto the postOrder, and move on:

Thanks to dasblinkenlight http://stackoverflow.com/users/335858/dasblinkenlight


*/

#define MAX 7
typedef vector<int> vi;
typedef vector<vi > vvi;

bool visited[MAX]={0};

int main(){
	char fileName[]="dag1.txt";
	vvi graph=readGraph(fileName);
	
	
	stack<pair<bool,int> > dfs;
	stack<int> postOrder;//dfs
	vi newVec;
	vi::iterator it;
	
	for(int i=0;i<MAX;i++){
		if(visited[i]==false){
			cout<<"DFS "<<i<<endl;
			//dfs(i);
			dfs.push(make_pair(false,i));
		}	
		
		while(!dfs.empty()){
			pair<bool,int> node=dfs.top();
			dfs.pop();
			if (node.first) {
				postOrder.push(node.second);
				continue;
			}
			visited[node.second]=true;
			dfs.push(make_pair(true, node.second));
			newVec=graph[node.second]; //vector of neighboors
			for(it=newVec.begin();it!=newVec.end();it++){
				int son=*it;
				if(visited[son]==false){
				    dfs.push(make_pair(false, son));
				}
			}
		}
		
	}

	cout<<"Reversed post Order"<<endl;	
	while(!postOrder.empty()){
		cout<<postOrder.top()<<endl;
		postOrder.pop();
	}
	

	return 0;
}










