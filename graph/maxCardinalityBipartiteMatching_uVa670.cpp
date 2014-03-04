#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;


//UVa 670 max cardinality bipartite matching. 
/*
set1 s1 of nodes: hunter's spots.
set2 s2 of nodes: interesting places for the dog
there is an edge between nodes in set1 and set2 only if the distance

dist(s1(i),s1(i-1)) >= [ dist (s1(i-1),s2(i)) + dist(s2(i),s1(i)) ] 
because dog can go twice as fast as the hunter


input


4

4 5
1 4 5 7 5 2 -2 4
-4 -2 3 9 1 2 -1 3 8 -3
2 2
1 1 5 5
1 3 3 5
4 5
1 4 5 7 5 2 -2 4
-4 -2 3 9 1 2 -1 3 8 -3
2 2
1 1 5 5
1 3 3 5


output
6
1 4 3 9 5 7 5 2 1 2 -2 4

3
1 1 1 3 5 5

6
1 4 3 9 5 7 5 2 1 2 -2 4

3
1 1 1 3 5 5

*/



typedef pair<int,int> ii;

vector<ii > nodes1,nodes2;

int testC,s1nodes,s2nodes;


// bipartite graph (constructed after) for max flow
#define MAX 210
vector<int> adjList[MAX];
vector<int>::iterator it;
int cap[MAX][MAX];
int flows[MAX][MAX];




//checks if the distance of interesting place is reachable (dog goes twice as fast)
//in order to meet hunter at next spot
bool okDist(int hunter1x,int hunter1y,int hunter2x,int hunter2y,int dog1x,int dog1y)
{
	bool answer=false;
	int hunterD=( (hunter2x-hunter1x)*(hunter2x-hunter1x) + (hunter2y-hunter1y)*(hunter2y-hunter1y) );
	int dogD1 = (hunter2x-dog1x)*(hunter2x-dog1x) + (hunter2y-dog1y)*(hunter2y-dog1y);
	int dogD2 = (hunter1x-dog1x)*(hunter1x-dog1x) + (hunter1y-dog1y)*(hunter1y-dog1y);
	double hunterDsq=sqrt(hunterD);
	double dogD1sq=sqrt(dogD1);
	double dogD2sq=sqrt(dogD2);
	//cout<<"op "<<2*hunterDsq - (dogD1sq +dogD2sq)<<endl;
	answer= 2*hunterDsq - (dogD1sq +dogD2sq) >= -1e-10 ;
	//if(answer)	cout<<"dists "<<2*hunterDsq<<" dog: "<<(dogD1sq +dogD2sq)<<endl;
	return answer;
}


int main()
{
	int x,y,maxFlow;
	cin>>testC;
	string blank="";
	while(testC--){
		maxFlow=0;
		cin>>s1nodes>>s2nodes;
		nodes1.clear();
		nodes2.clear();
		for(int i=0;i<s1nodes;i++){
			cin>>x>>y;
			nodes1.push_back(make_pair(x,y));
		}		
		for(int i=0;i<s2nodes;i++){
			cin>>x>>y;
			nodes2.push_back(make_pair(x,y));
		}
	
		memset(cap,0,sizeof(cap));
		memset(flows,0,sizeof(flows));
		for(int i=0;i<MAX;i++)
			adjList[i].clear();
		
		
		int source=0;
		int sink=209;
		
		bool sourced[MAX]={0};
		bool sinked[MAX]={0};
		
		for(int i=0;i<s1nodes-1;i++){
			for(int j=0;j<s2nodes;j++){
				if(okDist(nodes1[i].first,nodes1[i].second, nodes1[i+1].first,nodes1[i+1].second, nodes2[j].first,nodes2[j].second )){
					adjList[i+1].push_back(j+s1nodes); //first hunter node doesn't matter
					adjList[j+s1nodes].push_back(i+1); //back edge
					cap[i+1][j+s1nodes]=1; //directed graph
					if(sourced[i+1]==false){ //already gave this the dummy source
						adjList[source].push_back(i+1);
						adjList[i+1].push_back(source);
						cap[source][i+1]=1;
						sourced[i+1]=true;
					}
					if(sinked[j+s1nodes]==false){ //dummy sink not added
						adjList[j+s1nodes].push_back(sink);
						cap[j+s1nodes][sink]=1;
						sinked[j+s1nodes]=true;
						//cout<<"sinked "<<j+s1nodes<<endl;
					}
					//cout<<"added "<<i+1<<" and "<<j<<endl;
				}
			}
		}
		
		
		//max Flow now, with edge capacities 1 forcing to pair 1-to-1 (matching)
		//cout<<"---------max flow part"<<endl;
		
		while(1){ //while there are augmenting paths
			queue<int> bfs;
			int parents[MAX];
			for(int i=0;i<MAX;i++)
				parents[i]=-1;
			bfs.push(source);
			while(!bfs.empty()){ //find augmenting paths
				int node=bfs.front();
				//cout<<"node "<<node<<endl;
				bfs.pop();
				if(node==sink)	break;
				vector<int> neighbors = adjList[node];
				for(it=neighbors.begin();it!=neighbors.end();it++){
					//cout<<"neighbor "<<*it<<" parents "<<parents[*it]<<endl;
					if((cap[node][*it]-flows[node][*it])>0 && parents[*it]==-1){
						bfs.push(*it);
						parents[*it]=node;	
					}
				}
				
			}
			
			//cout<<"after bfs"<<endl;
		
			//find minEdge along path found and add the flow to the edges
			int f=0;
			int minEdge=1<<30-1;
			int q;
			
			if(parents[sink]==-1) break; //wasn't reached
			for(q=sink;q!=source;q=parents[q]){
				//cout<<"\tpath "<<q<<endl;
				minEdge=min(minEdge,cap[parents[q]][q]-flows[parents[q]][q]);
			}
			
			if(q==source)
				f=minEdge;
			//cout<<"f = "<<f<<endl;
			if(f==0) 
				break;
			//add the flows to the edges
			for(q=sink;q!=source;q=parents[q]){
				flows[parents[q]][q]+=f;
				flows[q][parents[q]]-=f;
			}
			
			maxFlow+=f;
		}
		//cout<<"Max Flow is "<<maxFlow<<endl;
		
		string space="";
		cout<<blank<<s1nodes+maxFlow<<endl;
		blank="\n";
		for(int i=0;i<s1nodes;i++){
			for(int j=0;j<s2nodes;j++){
				if(i>0 && flows[i][j+s1nodes]>0){
					cout<<" "<<nodes2[j].first<<" "<<nodes2[j].second;	
				}
			}
			cout<<space<<nodes1[i].first<<" "<<nodes1[i].second;
			space=" ";
		}
		cout<<endl;
		
	
	
	
	
	
	}





	return 0;

}
