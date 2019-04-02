#include "BSTree.h"

using namespace std;

BSTree::BSTree(){
	root = 0;
}

BSTree::~BSTree(){
	if(!root) return;
	destructor(root);
}

void BSTree::destructor(Node* & node) const{
	if(!node) return;
	destructor(node->left);
	destructor(node->right);
	delete node;
	node = 0;
}

void BSTree::insert(const string& data){
	insert(data, root);
}

void BSTree::insert(const string & data, Node* & node) const{
	if(!node){
		node = new Node(data);
		return;
	} else if(data == node->data){
		node->count++;
		return;
	} else if(data[0] < node->data[0]){
		insert(data, node->left);
	} else{
		insert(data, node->right);
	}
}

bool BSTree::search(const string& data) const{
	if(!searchNode(data, root)){ return false; }
	return data == searchNode(data, root)->data;
} /* recurive */

Node* BSTree::searchNode(const string& data, Node* node) const{
	if(!node) return 0;
	else if(node->data == data) return node;
	else if(node->data[0] > data[0]) return searchNode(data, node->left);
	else return searchNode(data, node->right);
}

const string BSTree::largest() const{
	return largest(root);
}

const string BSTree::largest(Node* node) const{
	if(!node) return ""; 

	Node* large = 0;
	while(node){
		large = node;
		node = node->right;
	}
	return large->data;
}

const string BSTree::smallest() const{
	return smallest(root);
}

const string BSTree::smallest(Node* node) const{
	if(!node) return "";
	Node* small = node;
	while(node){
		small = node;
		node = node->left;
	}
	return small->data;
}

int BSTree::height(const string& data) const{
	if(!search(data)) return -1;
	if(!root) return 0;

	int count = height(data, root);
	Node* start = root;

	while(start->data != data){
		if(start->data[0] < data[0]){
			start = start->right;
		} else{
			start = start->left;
		}
		count--;
	}
	if(!start->left && !start->right) return 0;

	return count;
}

int BSTree::height(const string& data, Node* node) const{
	if(!node) return 0;

	int count = 0;

	while(data != node->data){
		if(node->data[0] < data[0]){
			node = node->right;
			count++;
		} else{
			node = node->left;
			count++;
		}
	}
	while((node->right || node->left)){
		if(node->left){
			node = node->left;
			count++;

		} else if(node->right){
			node = node->right;
			count++;
		}
	}

	return count;
}

void BSTree::remove(const string& data){
	if(!search(data)) return;

	remove(data, root);
} /* recurive */

void BSTree::remove(const string& data, Node* & node) const{
	if(!node) return;
	// good
	if(!search(data)) return;
	// item not found
	// good

	if(node->data == data){
		// more than one
		// good
		if(node->count > 1){
			node->count--;
			return;
		}
		// leaf
		else if(!node->left && !node->right){
			delete node;
			node = 0;
			return;
			// one child
		} else if(!node->left || !node->right){
			// has right child
			if(!node->left){
				node->data = smallest(node->right);
				node->count = searchNode(node->data, node->right)->count;
				if(searchNode(node->data, node->right)->count > 1) searchNode(node->data, node->right)->count = 1;
				remove(node->data, node->right);
			// has left child
			} else if(!node->right){
				node->data = largest(node->left);
				node->count = searchNode(node->data, node->left)->count;
				if(searchNode(node->data, node->left)->count > 1) searchNode(node->data, node->left)->count = 1;
				remove(node->data, node->left);
			}
			// two children
		} else if(node->left && node->right){

			node->data = largest(node->left);
			node->count = searchNode(node->data, node->left)->count;
			if(searchNode(node->data, node->left)->count > 1) searchNode(node->data, node->left)->count = 1;
			remove(node->data, node->left);
		}
	} else if(data[0] < node->data[0]){
		remove(data, node->left);
	} else if(data[0] > node->data[0]){
		remove(data, node->right);
	}
}

void BSTree::preOrder(){
	preOrder(root);
	cout << endl;
} /* recurive */

void BSTree::inOrder(){
	inOrder(root);
	cout << endl;
} /* recurive */

void BSTree::postOrder(){
	postOrder(root);
	cout << endl;
} /* recurive */

void BSTree::preOrder(Node* node) const{
	if(!node) return;
	else
		cout << node->data << "(" << node->count << "), ";
		preOrder(node->left);
		preOrder(node->right);
} /* recurive */

void BSTree::inOrder(Node* node) const{
	if(!node) return;
	else 
		inOrder(node->left);
		cout << node->data << "(" << node->count << "), ";
		inOrder(node->right);
} /* recurive */

void BSTree::postOrder(Node* node) const{
	if(!node) return;
	else
		postOrder(node->left);
		postOrder(node->right);
		cout << node->data << "(" << node->count << "), ";
} /* recurive */