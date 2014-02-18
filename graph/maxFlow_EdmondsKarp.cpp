#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//Edmonds Karp algorithm is an implementation of Ford-fulkerson algo that uses BFS to find augmenting paths

//test input: one edge per line: node1 node2 capacity
/*
source=0 sink =5

0 5
0 1 10
1 2 9
2 5 10
2 4 15
1 4 15
1 3 4
0 3 5
3 4 8
4 5 10
0 6 15
3 6 4
6 7 16
7 3 6
4 7 15
7 5 10
-1

(From coursera's princeton Algo 2 video 6-2)
MAX FLOW ANS
0 1 10/10
0 3 5/5
0 6 13/15
1 2 8/9
1 3 0/4
1 4 2/15
2 4 0/15
2 5 8/10
3 4 8/8
3 6 0/4
4 5 10/10
4 7 0/15
6 7 13/16
7 3 3/6
7 5 10/10


*/

#define MAX 110
int residualCapacity[MAX][MAX];
int parent[MAX];

vector<int> adjList[MAX];
vector<int>::iterator it;

int s,t,f,maxFlow=0,n1,n2,capacity,minEdge;
int big=1<<30-1;
	
void augmentPath(int node){
	if(node==s){
		f=minEdge;
		return;
	}
	else if(parent[node]!=-1){ //to assert it reached the sink
		int previous=parent[node];
		minEdge=min(minEdge,residualCapacity[previous][node]);
		augmentPath(previous);//after recursion, so f is already min_edge do the following:
		//cout<<"\t"<<node<<endl;
		residualCapacity[previous][node]-=f; //forward_edge increase flow, decrease residual 
		residualCapacity[node][previous]+=f; //backward_edge decrease flow, increase residual 
	}
	
	
}


int main()
{
		
	memset(residualCapacity,0,sizeof(residualCapacity));

	
	for(int i=0;i<MAX;i++)
		adjList[i].clear();
		
	
	cin>>s>>t;
	while(cin>>n1 && n1!=-1){
		cin>>n2>>capacity;
		//undirected edges, for the algorithm
		//edges go both ways because flow can be substracted from one edge (opposite direction) to put into another one.
		//There could be more than 1 edge from i to j, so add capacities
		
		residualCapacity[n1][n2]+=capacity;
		//residualCapacity[n2][n1]+=capacity; //only if it's undirected graph
		adjList[n1].push_back(n2);
		adjList[n2].push_back(n1);
	}

	while(1){ //while there are augmenting paths
		f=0;
		//cout<<"MAIN WHILE "<<endl;
		for(int i=0;i<MAX;i++)
			parent[i]=-1;

		queue<int> bfs;
		parent[s]=s;
		bfs.push(s);
		while(!bfs.empty()){
			//cout<<"BFS WHILE "<<bfs.front()<<endl;
			int node=bfs.front();
			bfs.pop();
			if(node==t)	break; //stop BFS if we reach sink, should emptystack but we redeclare eachtime
			vector<int> neighbors=adjList[node];
			for(it=neighbors.begin();it!=neighbors.end();it++){
				//cout<<"\t neighbor "<<*it<<endl;
				if(residualCapacity[node][*it]>0 && parent[*it]==-1){ //positive residual capacity & not visited
					parent[*it]=node; //for backtracking the path
					bfs.push(*it);				
				}	
			}
		}
		
		//after BFS backtrack the path found and augment the flows in each edge before BFS again
		minEdge=big;
		augmentPath(t);
		if(f==0)	break; // no more flow to add
		maxFlow+=f;
		//cout<<"added flow "<<f<<endl;
	}

	cout<<"MaxFlow is "<<maxFlow<<endl;






	return 0;
}















