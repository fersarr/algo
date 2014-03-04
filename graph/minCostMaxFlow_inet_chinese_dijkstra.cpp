#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <map>
#include <list>
#define MAX 1l << 62

//too slow, TLE (time limit exceeded) 

using namespace std;

typedef pair<int,int>   ii;
typedef pair<long long,long long>   llll;
typedef vector<int>     vi;
typedef vector<ii>      vii;
typedef vector<llll>      vllll;
typedef vector<long long>      vll;
typedef vector<vi>     vvi;
typedef vector<vii>    vvii;

int N,M;
long long D,K;
llll mm[105][105];
int parent[105];
long long minT = 0;

void augment(){
    int nc = N-1;
    vi S;
    while(nc >= 0){
        S.push_back(nc);
        nc = parent[nc]; 
    }
    
    long long minEdge = MAX; //min residual capacity edge
    reverse(S.begin(),S.end());
    for(int i=1;i<S.size();i++){
        int u = S[i-1], v = S[i];
        minEdge = min(minEdge,mm[u][v].first);
    }
    
    if(D < minEdge)  
    	minEdge = D;
    
    D -= minEdge;//each time we have less data to flow through network
    
    for(int i=1;i<S.size();i++){
        int u = S[i-1], v = S[i];
        mm[u][v].first -= minEdge; //flow
        mm[v][u].first += minEdge;
        minT += minEdge * mm[u][v].second; //flow * edgeCost = cost
        // printf(" u,v = %d,%d, minEdge = %d, second = %d, minT = %ld\n",u,v,minEdge,mm[u][v].second, minT);
    }
}

int cnt[105];

int main(){
    while(cin >> N >> M){
        minT = 0;
        memset(mm,0,sizeof mm);
        int a,b; 
        long long c;
        for(int i=0;i<M;i++){
            cin >> a >> b >> c;
            a--;b--;
            mm[a][b].second = c;	//cost
            mm[b][a].second = -c;
            mm[a][b].first =-1;		//flowCapacity - all have the same
            mm[b][a].first =-1;
        }
        cin >> D >> K;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(mm[i][j].first == -1){
                    mm[i][j].first = K; //flowCapacity - all have the same
                }
            }
        }

        // then do the max-flow alg -- using dijkstra's to find the shortest path
        while(true){
            // init first
            for(int i=0;i<N;i++)    
            	parent[i] = -2;

            priority_queue<llll,vllll,greater<llll > > q; //cost-node : pair<long long, long long>
            vll dist(N,MAX);

            q.push(llll(0,0));
            dist[0] = 0;

            memset(cnt,0,sizeof cnt);

            while(!q.empty()){
                int cost = q.top().first;
                int u = q.top().second;q.pop();
                if(cost > dist[u])    //if we reached this node in a better way before, ignore this pass
                	continue;

                if(u == N - 1)  break;  // avoid negative cycle. N-1 is sink
				
                cnt[u]++;
                if(cnt[u] > N)  break;
                dist[u] = cost;
                for(int i=0;i<N;i++){
                    int nd = cost + mm[u][i].second; //costSoFar +edgeCost
                    if(nd < dist[i] && mm[u][i].first > 0){
                        // printf(" u,i = %d, %d, mm[u][i] = %d\n",u,i,mm[u][i].first);
                        parent[i] = u;
                        q.push(llll(nd,i));
                    }
                }
            }
            if(parent[N-1] != -2){
                // printf("parent[N-1] = %d\n",parent[N-1]);
                augment();
            }
            else break;
            if(D <= 0)  break;
        }
        if(D > 0) cout << "Impossible." << endl;
        else cout << minT << endl;
    }
    return 0;
}
