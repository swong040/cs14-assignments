#include "Tree.h"
#include <algorithm>

using namespace std;

  // string small;
  // string large;

  // Node *left;
  // Node *middle;
  // Node *right;
  // Node *parent;
Tree::Tree( ){ root = 0; }

Tree::~Tree( ){
	delete root;
	// destructor(root);
	root = 0;
}

// good
void Tree::inOrder(){ inOrder(root); cout << endl; }
void Tree::inOrder(Node* node){
	if(!node) return;
	else if(threeNode(node)){
		inOrder(node->left);
		cout << node->small << ", ";
		inOrder(node->middle);
		cout << node->large << ", ";
		inOrder(node->right);
	} else if(twoNode(node)){
		inOrder(node->left);
		cout << node->small << ", ";
		inOrder(node->right);
	}
}
// good
void Tree::preOrder( ){ preOrder(root); cout << endl; }
void Tree::preOrder(Node* node){
    if(!node) return;
	else if(threeNode(node)){
		cout << node->small << ", ";
		preOrder(node->left);
		cout << node->large << ", ";
		preOrder(node->middle);
		preOrder(node->right);
	} else if(twoNode(node)){
		cout << node->small << ", ";
		preOrder(node->left);
		preOrder(node->right);
	}
}
// good
void Tree::postOrder( ){ postOrder(root); cout << endl; }
void Tree::postOrder(Node* node){
	if(!node) return;
	else if(threeNode(node)){
		postOrder(node->left);
		postOrder(node->middle);
		cout << node->small << ", ";
		postOrder(node->right);
		cout << node->large << ", ";
	} else if(twoNode(node)){
		postOrder(node->left);
		postOrder(node->right);
		cout << node->small << ", ";
	}
}

bool Tree::isLeaf(Node* node) const{
	return (!node->left && !node->middle && !node->right);
}

bool Tree::twoNode(Node* node) const{
	return (node->large == "");
}

bool Tree::threeNode(Node* node) const{
	return (node->large != "");
}
// good
bool Tree::search(const string & data){
	if(!root) return false;
	if(!searchNode(data, root)) return false;
	return data == searchNode(data, root)->small || data == searchNode(data, root)->large;
}
// good
Node* Tree::searchNode(const string & data, Node* &node) const{
	if(!node) return 0;
	if(data == node->small || data == node->large){
		return node;
	} else if(twoNode(node)){
		if(data[0] < node->small[0]){
			searchNode(data, node->left);
		} else{
			searchNode(data, node->right);
		}
	} else if(threeNode(node)){
		if(data[0] < node->small[0]){
			searchNode(data, node->left);
		} else if (data[0] < node->large[0]){
			searchNode(data, node->middle);
		} else if(data[0] > node->large[0]){
			searchNode(data, node->right);
		}
	}
}

void Tree::insert(const string & data){
// fix duplicates later
	if(search(data)) return;
	if(root == 0){
		root = new Node(data);
		return;
	} else if(isLeaf(root) && twoNode(root)){
		twoNodeInsert(data, root);
		// no need to move data's nodes
		return;
	} else if(isLeaf(root) && threeNode(root)){
		insert(data, root);

	// root is not leaf - sort accordingly
	} else if(twoNode(node)){
		if(data[0] < node->small[0]){
			insert(data, node->left);
		} else{
			insert(data, node->right);
		}
	} else if(threeNode(node)){
		if(data[0] < node->small[0]){
			insert(data, node->left);
		} else if (data[0] < node->large[0]){
			insert(data, node->middle);
		} else if(data[0] > node->large[0]){
			insert(data, node->right);
		}
	}
}

void Tree::insert(const string & data, Node* & node) const{
	if(isLeaf(node)){
		// case 1:
		if(twoNode(node)){ twoNodeInsert(data, node); return; }
		// case 2:
		else if(threeNode(node)){
			Node* nodeChildren[3];
			if(data[0] < node->small[0]){
				nodeChildren[0] = new Node(data); nodeChildren[1] = new Node(node->small); nodeChildren[2] = new Node(node->large);
			} else if(data[0] < node->large[0]){
				nodeChildren[0] = new Node(node->small); nodeChildren[1] = new Node(data); nodeChildren[2] = new Node(node->large);	
			} else{
				nodeChildren[0] = new Node(node->small); nodeChildren[1] = new Node(node->large); nodeChildren[2] = new Node(data);
			}
			node = nodeChildren[1];
			node->left = nodeChildren[0];
			node->right = nodeChildren[2];

			node->left->parent = node;
			node->right->parent = node;

			splitUp(node);
			
			cout << "end split" << endl;
			return;
		}
	} else if(twoNode(node)){
		if(data[0] < node->small[0]){
			insert(data, node->left);
		} else{
			insert(data, node->right);
		}
	} else if(threeNode(node)){
		if(data[0] < node->small[0]){
			insert(data, node->left);
		} else if (data[0] < node->large[0]){
			insert(data, node->middle);
		} else if(data[0] > node->large[0]){
			insert(data, node->right);
		}
	}
}    

// node is parent
void Tree::splitUp(Node* & node) const{
	cout << "split" << endl;
	// if parent is non exsistant (reached root)
	if(!node->parent) return;		// base case
	// if(!node->parent){ cout << "return" << endl; return;
	// if parent is two node
	 if(twoNode(node->parent)){
		twoNodeInsert(node->small, node->parent);
		node->parent->middle = node->left;
		node->parent->right = node->right;
		
		return;
	// if parent is three node
	} else if(threeNode(node->parent)){
		// finish
		cout << "three node split" << endl;
		Node* nodeChildren[3];
		if(node->small[0] < node->parent->small[0]){
			nodeChildren[0] = new Node(node->small); nodeChildren[1] = new Node(node->parent->small); nodeChildren[2] = new Node(node->parent->large);
		} else if(node->small[0] < node->parent->large[0]){
			nodeChildren[0] = new Node(node->parent->small); nodeChildren[1] = new Node(node->small); nodeChildren[2] = new Node(node->parent->large);	
		} else{
			nodeChildren[0] = new Node(node->parent->small); nodeChildren[1] = new Node(node->parent->large); nodeChildren[2] = new Node(node->small);
		}
		node->parent = nodeChildren[1];
		node->parent->left = nodeChildren[0];
		node->parent->right = nodeChildren[2];

		node->parent->left->parent = node;
		node->parent->right->parent = node;

		splitUp(node->parent);
	}
}

void Tree::twoNodeInsert(string data, Node* node) const{
	if(data[0] < node->small[0]){
		node->large = node->small;
		node->small = data;
	} else{
		node->large = data;
	}
	return;
}

void Tree::threeNodeInsert(Node* & node, Node* & parental) const{
	Node* parents[4];
	return;
}


void Tree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
//---------------------------------------------------
void Tree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        string parentData = "\"" + n->small;
        if(n->large != ""){
            parentData += ", " + n->large + "\"";
        }
        else{
            parentData += "\"";
        }
        outFS<<parentData << "[ label = "<<parentData<<"];"<<endl;
        
        if(n->left){
            string childData = "\"" + n->left->small;
            if(n->left->large!=""){
                childData += ", " + n->left->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->left);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
        
        if(n->middle){
            string childData =  "\""+n->middle->small;
            if(n->middle->large!=""){
                childData += ", " + n->middle->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->middle);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
        
        if(n->right){
            string childData =  "\"" + n->right->small;
            if(n->right->large != ""){
                childData += ", " + n->right->large + "\"";
            }
            else{
                childData += "\"";
            }
            visualizeTree(outFS,n->right);
            outFS<<parentData<<" ->  "<<childData<<";"<<endl;
        }
    }
}

