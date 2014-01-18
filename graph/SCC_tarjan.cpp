#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

/*Tarjan Algorithm: Strongly connected components (mostly Directed Gs)- 
big better than Kosaraju:
-only 1 DFS (instead of 2)
-inverse graph not needed


Testing input:
8
0 1
1 3
3 2
2 1
3 4
4 5
5 7
7 6
6 4
-1

3 SCCS: {0}, {1,2,3}, {4,5,6,7}


2nd INPUT //6 nodes including 0
5  
0 2
2 4
4 3
3 2
0 1
1 3
-1

*/

#define MAX 100

int n;
vector<int> graph[MAX];
bool visited[MAX];
bool in_stack[MAX]; //to check weather the node is in the current stack
stack<int> scc_stack;
int dfs_num[MAX], dfs_low[MAX];
int dfs_counter=0;

void dfs_tarjanSCC(int node)
{
	cout<<"dfs "<<node<<endl;
	dfs_num[node]=dfs_counter++;
	dfs_low[node]=dfs_num[node];
	visited[node]=true;	
	scc_stack.push(node);
	in_stack[node]=true;
	
	vector<int> neighbors=graph[node];
	for(vector<int>::iterator it=neighbors.begin();it!=neighbors.end();it++){
		if(visited[*it]==false)
			dfs_tarjanSCC(*it);
		if(in_stack[*it]==true)//only update dfs_low if *it is in the current SCC stack, even if has been visited(visited but not completed)
			dfs_low[node]=min(dfs_low[node],dfs_low[*it]);
	}

	cout<<"\t"<<node<<" dfs_low: "<<dfs_low[node]<<" dfs_num: "<<dfs_num[node]<<endl;
	if(dfs_num[node]==dfs_low[node]){ //this is the root of the current SCC
		cout<<"\tSCC: ";
		while(!scc_stack.empty() && scc_stack.top()!=node){ //second condition is to stop the while
			int vertex=scc_stack.top();
			scc_stack.pop();
			in_stack[vertex]=false;
			cout<<vertex<<" ";
		}
		cout<<scc_stack.top()<<endl;
		scc_stack.pop();
		in_stack[node]=false;
	}


}


int main()
{
	int from,to;
	while(cin>>n && n>0){
		memset(graph,0,sizeof(graph));
		memset(dfs_num,0,sizeof(dfs_num));
		memset(dfs_low,0,sizeof(dfs_low));	
		memset(visited,0,sizeof(visited));
		memset(in_stack,0,sizeof(in_stack));
		dfs_counter=0;
		
		while(cin>>from && from!=-1){
			cin>>to;
			//cout<<"edge "<<from<<" to "<<to<<endl;
			graph[from].push_back(to);
		}
		
		//should be done for all the disconnected components of the graph
		for(int i=0;i<n;i++)
			if(visited[i]==false)
				dfs_tarjanSCC(i);
		
		
		
	}







	return 0;
}
























