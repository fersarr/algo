#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "myGraphLibs.h"
using namespace std;

#define MAX 1000
typedef vector<int> vi;
typedef vector<vi > vvi;

int main()
{
	ifstream fin ("graph1.txt");
	string line;
	
	vvi graph;
	for(int i=0;i<MAX;i++){
		vi newVec;
		graph.push_back(newVec);
	}
	
	
	while(getline(fin,line)){
		stringstream ssline(line);
		int n1,n2;
		ssline>>n1>>n2;
		cout<<n1<<" "<<n2<<endl;
		graph[n1].push_back(n2);
	}
	
	graph2GraphViz(graph);
	return 0;
}
