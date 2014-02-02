#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//TARJAN algo to find articulation points and bridges. Runs in O(v+e) by using one DFS.


//UNDIRECTED graph1 testing input. It has no artic points
/*
6
0 1
1 2
1 4
3 4
4 5
-1
*/
//UNDIRECTED graph2 testing input. Vertex 1 is an artic point
/*
6
0 1
1 2
1 3
1 4
4 5
1 5
-1
*/
	
	
#define MAX 100
typedef pair<int,int> ii;
typedef vector<ii> vii;
vector<int> graph[MAX];

bool visited[MAX];
int parent [MAX] ,dfs_num[MAX], dfs_low[MAX];
int dfsCount=0, dfsRoot=0, rootChilds=0;
int n;
bool articPoints[MAX];

void tarjanAP_bridges(int node)
{
	//cout<<"dfs "<<node<<endl;
	dfs_num[node]=dfsCount++;
	dfs_low[node]=dfs_num[node];
	
	visited[node]=true;
	
	vector<int> neighbors=graph[node];
	for(vector<int>::iterator it=neighbors.begin();it!=neighbors.end();it++){
		if(visited[*it] == false){
			parent[*it]=node;
			if(dfsRoot==node) //root special case. AP if more than 1 child
				rootChilds++;
			tarjanAP_bridges(*it);
			dfs_low[node]=min(dfs_low[node],dfs_low[*it]);
			//for articulation points
			if(dfs_low[*it]>=dfs_num[node]){
				articPoints[node]=true;
			}
			//for bridges
			//if(dfs_low[*it]>=dfs_num[node]){
			//	cout<<"Bridge: edge "<<node<<","<<*it<<endl;
			//}
		}
		else{ // has already been visited before, it's a back edge, update dfs_low
			if(parent[node]!=*it){
				dfs_low[node]=min(dfs_low[node],dfs_num[*it]);
			}
		}
	}	



}

int main()
{
	
	cin>>n;
	memset(visited,0,sizeof(visited));
	memset(articPoints,0,sizeof(articPoints));
	memset(parent,0,sizeof(parent));
	memset(graph,0,sizeof(graph));
	rootChilds=0;
	dfsCount=0;
	dfsRoot=0;
	
	int from,to;
	while(cin>>from && from!=-1){
		cin>>to;
		graph[from].push_back(to);
		graph[to].push_back(from); //undirected graph
	}
	
	//this should be called for every vertex in case it's not all connected
	tarjanAP_bridges(dfsRoot);
	
	//cout<<"Articulation Points "<<endl;
	int count=0;
	for(int i=0;i<n;i++){
		if(articPoints[i]==true){
			if(i!=dfsRoot){
				cout<<"AP: "<<i<<endl;
				count++;
			}
		}
	}
	if(rootChilds>1){ //root special case
		count++;
		cout<<"root is AP"<<endl;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}

























