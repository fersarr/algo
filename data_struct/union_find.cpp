#include <iostream>
#include <vector>
using namespace std;


/*
Union-Find
Model a collection of disjoints sets
It has the ability to efficiently
-'find'which the item belongs to (or test if two belong to the same)
-'union' two disjoint sets into a bigger one
used in: kruskal MST, partioning, SCC or undirected graphs
set<type> is only good for a single set.
*/
vector<int> pSet; //parent set. pSet[i] indicates which set i belongs to, using the representative(parent) of that set.

void initSet(int _size) //initialize all sets as having just one element
{
	pSet.resize(_size);
	for(int i=0;i<_size;i++){
		pSet[i]=i;
	}
}

int findSet(int n){
	return pSet[n]==n? n : pSet[n]=findSet(pSet[n]); //recursively to the top for PATH COMPRESSION. 
}

//i will now belong to the set which j belongs to. It is done puting the parent of J'set as the parent of i's set parent.
void unionSet(int i,int j)
{
	pSet[findSet(i)]=findSet(j);
}

bool isSameSet(int i,int j)
{
	return findSet(i)==findSet(j);
}

void printSet()
{
	vector<int>::iterator it;
	int count=0;
	cout<<"Node\t\tSet Representative (parent)"<<endl;
	for(it=pSet.begin();it!=pSet.end();it++){
		cout<<count++<<"\t\t"<<*it<<endl;
	}
}

void pathCompression(){ //compress all paths
	vector<int>::iterator it;
	int count=0;
	for(it=pSet.begin();it!=pSet.end();it++){
		findSet(count++); //this is called on the element, not the parent (*it)
	}
}

void createSet(){
	pSet.push_back(pSet.size());
}

int main(){
	initSet(10);
	printSet();
	
	unionSet(0,1);
	printSet();
	
	unionSet(4,0); //should go recursively to 1 that is the parent of 0's set
	printSet();
	
	unionSet(1,7);
	printSet();
	
	unionSet(9,4); //9 should end up in 7 because of recursive path compression
	printSet();
	
	pathCompression();
	printSet();
	
	cout<<"same set 9 and 7 "<<isSameSet(9,7)<<endl;
	
	createSet();
	printSet();
	
	return 0;
}
















