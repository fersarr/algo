#include <iostream>
#include <vector>
using namespace std;

//bellman-ford detect negative cycles.
#define MAX 1010
vector<pair<int,int> > graph[MAX]; // graph[origin]=pair<destination,weight)
vector<pair<int,int> >::iterator it;
int dist[MAX];



//input
/* 2 cases, 1 is possible, second is not
2
3 3
0 1 1000
1 2 15
2 1 -42
4 4
0 1 10
1 2 20
2 3 30
3 0 -60
*/

int main()
{
	int testC,n,m,node1,node2,cost,big=1<<30;
	cin>>testC;
	while(testC--){
		cin>>n>>m;
		
		for(int i=0;i<n;i++)
			graph[i].clear();
		for(int i=0;i<n;i++)
			dist[i]=big;
		
		for(int i=0;i<m;i++){
			cin>>node1>>node2>>cost;
			graph[node1].push_back(make_pair(node2,cost));
		}
		
		//bellman-ford. Relax all E edges V-1 times
		dist[0]=0;
		for(int i=0;i<n-1;i++){
			for(int j=0;j<n;j++){
				vector<pair<int,int> > neighbors=graph[j];
				for(it=neighbors.begin();it!=neighbors.end();it++){
					int next=it->first;
					int weight=it->second;
					dist[next]=min(dist[next],dist[j]+weight);
				}
			}
		}
		
/* 		cout<<"dist "<<endl;
		for(int i=0;i<n;i++)
			cout<<i<<"\t"<<dist[i]<<endl;
		cout<<endl; */
		//Relax all E edges once more to check if there's a negative cycle that keeps making dist smaller
		
		bool negCycle=false;
		for(int j=0;j<n-1;j++){
			vector<pair<int,int> > neighbors=graph[j];
			for(it=neighbors.begin();it!=neighbors.end();it++){
				int next=it->first;
				int weight=it->second;
				if(dist[next]>dist[j]+weight)
					negCycle=true;
			}
		}
		
		cout<<(negCycle?"possible":"not possible")<<endl;
	}












	return 0;
}
