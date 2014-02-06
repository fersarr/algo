#include <iostream>
#include <map>
#include <sstream>
#include <cstdio>
using namespace std;

//Floyd-warshall and path reconstruction UVa 186

#define MAX 101
map<string,int> cityId;
string idCity[MAX];
string highways[MAX][MAX];
int graph[MAX][MAX];
int pre[MAX][MAX]; //predecessor matrix for reconstructing the path
int big=1<<29; //1<<30 + 1<<30 adds to overflow (negative number) and messes up the graph[][]

int totalMiles;
void printPath(int i,int j)
{
	//cout<<"called printPath "<<i<<","<<j<<endl;
	if(i==j){
		//printf("%-20s %-20s %-10s %5d\n",idCity[i].c_str(),idCity[j].c_str(),highways[i][j].c_str(),graph[i][j]);
		//totalMiles+=graph[i][j];
		return;
	}
	else{
		if(pre[i][j]==big)
			cout<<"No path possible"<<endl;
		else{
			printPath(i,pre[i][j]);
			printf("%-20s %-20s %-10s %5d\n",idCity[pre[i][j]].c_str(),idCity[j].c_str(),highways[pre[i][j]][j].c_str(),graph[pre[i][j]][j]);
			totalMiles+=graph[pre[i][j]][j];
		}
	}



}

int main()
{
	
	int nodeCount=0;
	string line,city1,city2,route;
	int miles,node1,node2;
	
	//initialize
	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			if(i!=j)
				graph[i][j]=big;
			else
				graph[i][j]=0;
			
	
	//first part of input
	while(getline(cin,line) && line!=""){
		stringstream ssline(line);
		getline(ssline,city1,',');
		getline(ssline,city2,',');
		getline(ssline,route,',');
		ssline>>miles;
		ssline.ignore(10,'\n');
		
		if(cityId.find(city1)==cityId.end()){
			idCity[nodeCount]=city1;
			cityId[city1]=nodeCount++;
		}
		node1=cityId[city1];
		if(cityId.find(city2)==cityId.end()){
			idCity[nodeCount]=city2;
			cityId[city2]=nodeCount++;
		}
		node2=cityId[city2];
		
		if(graph[node1][node2]>miles){
			highways[node1][node2]=route;
			highways[node2][node1]=route;
			graph[node1][node2]=miles;
			graph[node2][node1]=miles;
		}
		
		//cout<<"c1: "<<city1<<" c2: "<<city2<<" route: "<<route<<" miles: "<<miles<<endl;
	}
	
/* 	cout<<"Nodes ---- "<<endl;
	for(int i=0;i<nodeCount;i++){
		cout<<i<<" "<<idCity[i]<<endl;
	} */

	//predecessor matrix initialization
	for(int i=0;i<nodeCount;i++){
		for(int j=0;j<nodeCount;j++){
			if(graph[i][j]!=big){ //connected
				pre[i][j]=i;
			}
			else{
				pre[i][j]=-1;
			}
		}
	}

	//Floyd-Warshall APSP with path reconstruction
	for(int k=0;k<nodeCount;k++){ //intermid vertex
		for(int i=0;i<nodeCount;i++){
			for(int j=0;j<nodeCount;j++){
				if(graph[i][k]+graph[k][j]<graph[i][j]){
					graph[i][j]=graph[i][k]+graph[k][j];
					pre[i][j]=pre[k][j]; //to reconstruct the path					
				}
			}
		}
	}

	
	
	while(getline(cin,city1,',')){
		getline(cin,city2);
		//cout<<"query "<<city1<<" to "<<city2<<endl;
		node1=cityId[city1];
		node2=cityId[city2];
		totalMiles=0;
		cout<<endl<<endl;
		printf("%-20s %-20s %-10s %5s\n","From","To","Route","Miles");
		printf("%-20s %-20s %-10s %5s\n","--------------------","--------------------","----------","-----");
		printPath(node1,node2);
		printf("%-20s %-20s %-10s %5s\n","","","","-----");
		printf("%-20s %-20s %-10s %5d\n","","","Total",totalMiles);
	}














	return 0;
}
