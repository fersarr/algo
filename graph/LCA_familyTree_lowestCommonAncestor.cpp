#include <iostream>
#include <stack>
#include <map>
#include <cmath>
using namespace std;


//LOWEST COMMON ANCESTOR UVA 115
//single parent genealogy!! (no mom and dad)


//TEST INPUT
/*
b a
c a
d b
e b
f b
g b
h c
i c
j c
k c
l d
m d
n e
o e
p e
q f
r f
s g
t g
u g
v h
w h
x h
y i
z j
aa k
bb k
cc k
dd k
ee k
ff l
gg m
hh n
ii o
jj p
kk q
ll r
mm s
nn t
oo u
pp v
qq w
rr x
ss y
tt z
uu aa
vv bb
ww cc
xx dd
yy ee
zz ff
no.child no.parent
l ee
m k
v a
b zz
l m
d c
h g
ee ee
i z
c zz
t n
c y
a zz
q ff
h d
w d

*/


#define MAX 310
int m,n,nodeCount;
int parents[MAX];
//single parent genealogy!! (no mom and dad)


//p is relative of q as by which relationship: child, grand child, great child, parent, sibling,cousin
void queryLCA(int n1,int n2){
	//LCA: LOWEST COMMON ANCESTOR
	
	int p=n1,q=n2;
	
	int count=0;
	int pDistance[nodeCount];
	stack<int> pParents;
	while(parents[p]!=-1){
		pDistance[p]=count++;
		pParents.push(p);
		p=parents[p];
	}
	pDistance[p]=count++;
	
	
	count=0;
	int qDistance[nodeCount];
	stack<int> qParents;
	while(parents[q]!=-1){
		qDistance[q]=count++;
		qParents.push(q);
		q=parents[q];
	}	
	qDistance[q]=count++;
	
	if(p!=q){
		cout<<"no relation"<<endl;
		return;
	}
	int previous;
	while(p==q && !pParents.empty() && !qParents.empty()){
		previous=p; //same as q, last common ancestor
		p=pParents.top();
		q=qParents.top();
		pParents.pop();
		qParents.pop();
	}
 	if(p==q){ // one is descendant of the other
 		if(pParents.empty()){ //p is parent (or grand, etc) of q
 			int d=qDistance[q];
 			if(d==0)
 				cout<<"sibling"<<endl;
 			if(d==1)
 				cout<<"parent"<<endl;
 			if(d==2)
 				cout<<"grand parent"<<endl;
 			if(d>=3){
 				for(int i=0;i<d-2;i++)
 					cout<<"great ";
 				cout<<"grand parent"<<endl;
 			}
 		}
 		else{ //q is parent(or grand,etc.) of p
 			int d=pDistance[p];
 			if(d==0)
 				cout<<"sibling"<<endl;
 			if(d==1)
 				cout<<"child"<<endl;
 			if(d==2)
 				cout<<"grand child"<<endl;
 			if(d>=3){
 				for(int i=0;i<d-2;i++)
 					cout<<"great ";
 				cout<<"grand child"<<endl;
 			}
 		}
 	}
 	else{ //they are not parent/childs of eachother
 		m=pDistance[previous]-1; //distance to LCA
 		n=qDistance[previous]-1;
 		int k=min(n,m);
 		int j=abs(n-m);
 		if(k==0 && j==0)
 			cout<<"sibling"<<endl;
 		else if(j==0)
 			cout<<k<<" cousin"<<endl;
 		else
 			cout<<k<<" cousin removed "<<j<<endl;
 	}
	
}

int main()
{
	string s1,s2;
	nodeCount=0;
	map<string,int> exists;
	for(int i=0;i<MAX;i++)
		parents[i]=-1;
	//tree input
	while(cin>>s1>>s2 && s1!="no.child"){
		if(exists.find(s1)==exists.end()){
			exists[s1]=nodeCount++;
		}
		if(exists.find(s2)==exists.end()){
			exists[s2]=nodeCount++;
		}
		
		int n1=exists[s1];
		int n2=exists[s2];
		
		//cout<<"\t input"<<s1<<n1<<"------"<<s2<<n2<<endl;
		
		//input is child-parent (not parent-child)
		parents[n1]=n2;
	}

	//query input
	while(cin>>s1>>s2){
		if(exists.find(s1)==exists.end()){
			exists[s1]=nodeCount++;
		}
		if(exists.find(s2)==exists.end()){
			exists[s2]=nodeCount++;
		}
		//cout<<"---------------"<<endl;
		//cout<<"query "<<exists[s1]<<" and "<<exists[s2]<<endl;
		queryLCA(exists[s1],exists[s2]);
	}












	return 0;
}
