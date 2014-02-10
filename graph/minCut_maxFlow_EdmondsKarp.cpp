#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//mincut problem, undirected graph

int n,m,n1,n2,cost,s,t,f,maxFlow,big=1<<30-1,minEdge;

#define NCITIES 50
#define NEDGES 500
vector<int> adjList[NCITIES];
vector<int>::iterator it;
int parent[NCITIES]; //for path augmentation 
int resCapacity[NCITIES][NCITIES];
bool originalGraph[NCITIES][NCITIES]; //for mincut: originalGraph is needed because all the non-existant edges are initialized in zero

void augmentPath(int node)
{
	if(node==s){
		f=minEdge;
		return;
	}
	else if(parent[node]!=-1){
		minEdge=min(minEdge,resCapacity[parent[node]][node]);
		augmentPath(parent[node]);
		//cout<<"\t"<<parent[node]<<endl;
		resCapacity[parent[node]][node]-=f; //direct edge
		resCapacity[node][parent[node]]+=f; //back edge
	}



}

int main()
{
	while(cin>>n>>m && !(m==0 && n==0)){ //input n:cities and m:edges
		s=0;
		t=1;
		
		for(int i=0;i<n;i++){
			adjList[i].clear();
		}
		
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				resCapacity[i][j]=0;

		memset(originalGraph,0,sizeof(originalGraph));
		
		for(int i=0;i<m;i++){
			cin>>n1>>n2>>cost;
			n1--;
			n2--;
			resCapacity[n1][n2]+=cost;
			resCapacity[n2][n1]+=cost; //undirected graph
			adjList[n1].push_back(n2);
			adjList[n2].push_back(n1);
			originalGraph[n1][n2]=true;
			originalGraph[n2][n1]=true;
		}
		
		maxFlow=0;
		while(1){ //while there are augmenting paths
			//cout<<"WHILE "<<endl;
			for(int i=0;i<n;i++)
				parent[i]=-1;
			f=0;
			queue<int> bfs;
			bfs.push(s);
			parent[s]=s;
			while(!bfs.empty()){
				int node=bfs.front();
				bfs.pop();
				if(node==t) break;
				vector<int> neighbors=adjList[node];
				for(it=neighbors.begin();it!=neighbors.end();it++){
					if(resCapacity[node][*it]>0 && parent[*it]==-1){
						parent[*it]=node;
						bfs.push(*it);
						
					}	
				}		
			}
			
			minEdge=big;
			augmentPath(t);
			if(f==0) break;
			maxFlow+=f;		
		}
		
		//cout<<"Max flow is "<<maxFlow<<endl;
		
		//for min-cut edges:
		//use the visited[] from the last BFS. The edges that are part of the MINCUT are
		//the ones with starting vertex visited but ending vertex unvisited. And resCapacity==0
		//because they are saturated
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				//originalGraph is needed because all the non-existant edges are initialized in zero
				if(originalGraph[i][j] && resCapacity[i][j]==0 && parent[i]!=-1 && parent[j]==-1){ //its part of mincut
					cout<<i+1<<" "<<j+1<<endl;
				}
			}
		}
		
		cout<<endl;//BLANK AFTER EACH
	}











	return 0;
}
