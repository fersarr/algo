#include <iostream>
#include <queue>
using namespace std;

//Dijkstra (greedy) SSSP for weighted graph. From node 2 to all other nodes. (NUS book pg 74)
//input graph: (node1 node2 weight)
/*
1 3 3
1 4 6
2 1 2
2 3 7
2 5 6
3 4 5
5 4 1
-1

-output
distances 
1	2
2	0
3	5
4	7
5	6


*/

#define MAX 1000
int dist[MAX]; //keeps the smallest distance to the i-th node from the source (node 2)
typedef pair<int,int> pii;
priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > reachedNodes; // <best_dist_so_far_tothisnode,node>
vector<pair<int,int> > graph[MAX]; //all outgoing edges from node graph[node]: <neightbor,weight>
vector<pair<int,int> >::iterator it;

int main()
{
	int n1,n2,weight;
	int source=2;
	int big=1<<30;
	
	for(int i=0;i<MAX;i++)
		graph[i].clear();
	
	for(int i=0;i<MAX;i++)
		dist[i]=big; //INF is initial distance
		
	
	while(cin>>n1 && n1!=-1){
		cin>>n2>>weight;
		graph[n1].push_back(make_pair(n2,weight));
	}
	
	dist[source]=0;
	reachedNodes.push(make_pair(0,source));

	while(!reachedNodes.empty()){
		pair<int,int> pair1=reachedNodes.top();
		reachedNodes.pop();
		int weight2u=pair1.first;
		int u=pair1.second;
		//cout<<"node "<<u<<" bestW "<<weight2u<<endl;
		if(weight2u==dist[u]){ //Process each node ONLY ONCE, when we reach them using the min weight, 
							//since reachedNodes is sorted by weight, this is guaranteed
			vector<pair<int,int> > neighbors=graph[u];
			for(it=neighbors.begin();it!=neighbors.end();it++){
				int v=it->first;
				int weight2v=it->second;
				if(weight2u+weight2v<dist[v]){ // if this is cheaper way to node v
					dist[v]=weight2u+weight2v;
					reachedNodes.push(make_pair(dist[v],v));
				}		 	
			}
		}
	}
	
	
	cout<<"distances "<<endl;
	for(int i=0;i<MAX;i++){
		if(dist[i]<big)//only the ones that are connected, the ones that exist
			cout<<i<<"\t"<<dist[i]<<endl;
	}

























	return 0;
}
