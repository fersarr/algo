#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <queue>
using namespace std;

//huffman coding
//get the code book (map) for every symbol in the input text so that we can compress it.

#define ABC 256

//each symbol in the alphabet. Full binary tree nodes point to these.
struct Symbol{
	char c;
	double prob;
	string code;
	Symbol(char _c,double _prob){
		c=_c;
		prob=_prob;
	}
};


struct Node{
	double prob;
	Symbol * symbol;
	shared_ptr<Node> left,right;
	Node(double _prob,Symbol * _s,const shared_ptr<Node> & _left,const shared_ptr<Node> & _right){
		symbol=_s;
		prob=_prob;
		left=_left;
		right=_right;
	}
};


//cmpare function for min-heap
//lower frequencies first
struct Compare{
	bool operator()(const shared_ptr<Node> & a,const shared_ptr<Node> &b) const{
		return a->prob > b->prob; //bigger operator: lower first -> in heap its reverse
	}
};



//this is called from huffman_encoding()
void assign_huffman_code(const shared_ptr<Node> & curr,const string& code){
	
	if(curr!=nullptr){
		if(curr->symbol){ //not null means this contains a symbol (it's a leaf)
			curr->symbol->code=code;
		}
		else{ //non leafs, intermediary nodes, just concatenate code until leaf
			assign_huffman_code(curr->left,code+"0");
			assign_huffman_code(curr->right,code+"1");
		}
	
	}
}





void Huffman_Encoding(vector<Symbol> * symbols){


	//insert each symbol into a min-heap. Lower frequencies first.s
	priority_queue<shared_ptr<Node>,vector<shared_ptr<Node>>,Compare> minHeap;
	
	for(auto& s: *symbols){
		minHeap.push(make_shared<Node>(s.prob,&s,nullptr,nullptr));
	}
	
	//take the two of lowest frequencies and insert them into the Full binary tree
	//combine them and use the added (combined) frequency for the root node.
	//last in there will be root
	while(minHeap.size()>1){
		shared_ptr<Node> left=minHeap.top();
		minHeap.pop();
		shared_ptr<Node> right=minHeap.top();
		minHeap.pop();

		minHeap.push(make_shared<Node>(left->prob+right->prob,nullptr,left,right)); //nullptr for symbol beacuse only leaf have symbols
		
	}	
	
	//traverse the full binary tree and assign code to each Symbol struct
	assign_huffman_code(minHeap.top(),"");
	
}











int charMap[ABC];

int main(){

	ifstream fin("text.txt");
	
	string word;
	
	for(int i=0;i<ABC;i++){
		charMap[i]=0;
	}

	int allChars=0;
	
	//count word frequency
	while(fin>>word){
		//cout<<word<<endl;
		for(int i=0;i<word.length();i++){
			if(word[i]>=0 && word[i]<256){ //avoid weird symbols
				charMap[word[i]]++;
				allChars++;
			}
		}
	}


	for(int i=0;i<ABC;i++){
		if(charMap[i]>0){
			char c=i;
			cout<<c<<": "<<charMap[i]<<endl;
		}
	}

	cout<<"Number of Chars: "<<allChars <<endl;
	
	vector<Symbol> symbols;
	
	//get the probability of every char
	cout<<"Frequencies"<<endl;
	for(int i=0;i<ABC;i++){
		if(charMap[i]>0){
			char c=i;
			double prob=charMap[i]/(allChars*1.0);
			symbols.push_back(Symbol(i,prob));
			cout<<c<<": "<<prob<<endl;
		}
	}


	Huffman_Encoding(&symbols);
	
	cout<<"------------"<<endl;
	for(auto& symbol:symbols){
		cout<<"symbol: "<<symbol.c<<"\tcode: "<<symbol.code<<endl;
	}







	return 0;
}
