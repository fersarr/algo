#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
#include "myGraphLibs.h"

#define MAX 15

bool visited[MAX]={0};

/* IN BFS it is necessary to mark node as visited when they are added to the queue. Otherwise, they could be added twice, 
each time from a different branch */

int main(){

	char fileName[20]="graph1.txt";
	vvi graph=readGraph(fileName); //obtain adjacency list
	//graph2GraphViz(graph); //for visualization
	
	queue<int> bfs;
	vi newVec;
	vi::iterator it;
	
	for(int i=0;i<MAX;i++){
		if(visited[i]==false){
			bfs.push(i);
			cout<<"PUSH "<<i<<endl;
			visited[i]=true;
			
			while(!bfs.empty()){
				int node=bfs.front();
				bfs.pop();
				newVec=graph[node];
				
				for(it=newVec.begin();it!=newVec.end();it++){
					//cout<<"from "<<node<<" view "<<*it<<endl;
					if(visited[*it]==false){
						cout<<"push "<<*it<<endl;
						visited[*it]=true;
						bfs.push(*it);
					}
				}
				
			
			}
		
		}
	
	}
	
	return 0;
}


