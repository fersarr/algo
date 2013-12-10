#include <iostream>
using namespace std;

struct TreeNode{
	int value;
	bool flag;
	TreeNode *left;
	TreeNode *right;
};

TreeNode* newNode(int val){
	TreeNode* node=new TreeNode();
	node->value=val;
	node->flag=false;
	node->left=NULL;
	node->right=NULL;
	return node;
}

void insertValue(TreeNode* node,int value){
	if(value<node->value){ //left
		if(node->left==NULL){
			TreeNode* son=newNode(value);
			node->left=son;
		}
		else{
			insertValue(node->left,value);
		}
	}
	else{ //right
		if(node->right==NULL){
			TreeNode* son=newNode(value);
			node->right=son;
		}
		else{
			insertValue(node->right,value);
		}
	}
}

void inOrder(TreeNode* node,int level)
{
	cout<<level<<": "<<node->value<<endl;
	if(node->left!=NULL)
		inOrder(node->left,level+1);
	if(node->right!=NULL)
		inOrder(node->right,level+1);
}


int search(TreeNode* node,int value){
	if(node->value==value)
		return value;
	int sonSearch;
	if(value < node->value && node->left!=NULL){ //search left
		sonSearch=search(node->left,value);
	}
	else if(node->right!=NULL)
		return search(node->right,value);	
	else
		return -1;
}


int main()
{
	TreeNode *tree=newNode(17);
	insertValue(tree,7);
	insertValue(tree,21);
	insertValue(tree,3);
	insertValue(tree,8);
	insertValue(tree,2);
	inOrder(tree,0);
	
	int ans=search(tree,9);
	cout<<"Search: "<<ans<<endl;
	
	ans=search(tree,2);
	cout<<"Search: "<<ans<<endl;
	
	return 0;
}








