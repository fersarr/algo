//Given an input graph, as an adjacency list (vector<vector<int> >), outputs a .gv file for visualization using graphViz.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#define MAX 10000
typedef vector<int> vi;
typedef vector<vi> vvi;

//void graph2GraphViz(vvi&);

/* int main()
{
	cout<<"graph 2 GraphViz - Written to file \n\n";
	ifstream fin("graph1.txt");
	string line;
	
	vvi graph;
	for(int i=0;i<MAX;i++){
		vi newVec;
		graph.push_back(newVec);
	}
	
	//Read file and create graph
	while(getline(fin,line)){
		stringstream ss(line);
		int n1,n2;
		ss>>n1>>n2;	
		graph[n1].push_back(n2);
	}
	
	
	graph2GraphViz(graph);
	return 0;
}
 */

void graph2GraphViz(vvi &graph){
	ofstream fout("graphVizFile.gv");
	fout<<"digraph G{\n";	

	vector<vector<int> >::iterator it;
	int node1=0;
	for(it=graph.begin();it!=graph.end();it++){
		vi::iterator it2;
		vi vec=*it;
		for(it2=vec.begin();it2!=vec.end();it2++){
			fout<<"\""<<node1<<"\"->\""<<*it2<<"\";\n";
		}
		node1++;
	}	
	fout<<"}\n";	
	fout.close();
	
}
















