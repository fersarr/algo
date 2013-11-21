#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
#include "myGraphLibs.h"

#define MAX 15

bool visited[MAX]={0};



int main(){

	char fileName[20]="graph1.txt";
	vvi graph=readGraph(fileName); //obtain adjacency list
	//graph2GraphViz(graph); //for visualization
	
	stack<int> dfs;
	vi newVec;
	vi::iterator it;
	
	for(int i=0;i<MAX;i++){
		if(visited[i]==false){
			dfs.push(i);
			visited[i]=true;
			
			while(!dfs.empty()){
				int node=dfs.top();
				dfs.pop();
				visited[node]=true;
				newVec=graph[node];
				
				for(it=newVec.begin();it!=newVec.end();it++){
					//cout<<"from "<<node<<" view "<<*it<<endl;
					if(visited[*it]==false){
						cout<<"push "<<*it<<endl;
						dfs.push(*it);
					}
				}
				
			
			}
		
		}
	
	}
	
	return 0;
}


