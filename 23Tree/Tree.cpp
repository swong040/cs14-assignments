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
	cout << "fuck" << endl;
	if(!root) cout << "no good" << endl; return false;
	cout << "good" << endl;
	return searchNode(data, root)->small == data || searchNode(data, root)->large == data;
}
// good
Node* Tree::searchNode(const string & data, Node* node) const{
	if(!node) return 0;
	while(!isLeaf(node)){
		if(node->small == data || node->large == data){
			break;
		} else if(data < node->small){
			node = node->left;
		} else if(threeNode(node) && data <= node->large){
			node = node->middle;
		} else{
			node = node->left;
		}
	}
	return node->parent;
}

void Tree::remove(const string& data){

	
}

void Tree::insert(const string & data){
	if(search(data)) return;
	
	if(!root){
		root = new Node(data);
	} else if(isLeaf(root)){
		if(twoNode(root)){
			twoNodeInsert(data, root);
		} else if(threeNode(root)){
			Node* dataNode = new Node(data);
			root = split(root, dataNode, 0);
		}
	} else{
		//insert helper
		insert(data, root);
	}
}

void Tree::insert(const string & data, Node* & node) const{
	Node* Data = new Node(data);
	if(isLeaf(node)){
		// leaf and two node
		if(twoNode(node)){
			twoNodeInsert(data, node);
		// leaf and three node
		} else if(threeNode(node)){
			int child = nodeChild(node, node->parent);
			Node* splitNode = split(node, Data, child);
			
			while(root != node->parent){
				if(twoNode(node->parent)){
					twoNodeInsert(splitNode->small, node->parent);
					int child = nodeChild(node, node->parent);
					if(child == 0){
						node->parent->left = splitNode->left;
						node->parent->middle = splitNode->right;

						splitNode->left->parent = splitNode->right->parent = node->parent;
					} else if(child == 2){
						node->parent->middle = splitNode->left;
						node->parent->right = splitNode->right;
	
						splitNode->left->parent = splitNode->right->parent = node->parent;
					}
					break;
				} else{
					child = nodeChild(node, node->parent);
					splitNode = split(node->parent, splitNode, child);
				}
			}
			if(root == node->parent){
				child = nodeChild(node, node->parent);
				if(twoNode(node->parent)){
					twoNodeInsert(splitNode->small, node->parent);
					if(child == 0){
						node->parent->left = splitNode->left;
						node->parent->middle = splitNode->right;
	
						splitNode->left->parent = splitNode->right->parent = node->parent;
					} else if(child == 2){
						node->parent->middle = splitNode->left;
						node->parent->right = splitNode->right;
						
						splitNode->left->parent = splitNode->right->parent = node->parent;
					}
				} else if(threeNode(node->parent)){
					child = nodeChild(node, node->parent);
					node = split(node->parent, splitNode, child);
				}
			}
		}
	// insert at non leaf
	} else{
		if(twoNode(node)){
			if(data  < node->small ){
				insert(data, node->left);
			} else{
				insert(data, node->right);
			}
		} else if(threeNode(node)){
			if(data  < node->small ){
				insert(data, node->left);
			} else if(data  < node->large ){
				insert(data, node->middle);
			} else if(data  > node->large ){
				insert(data, node->right);
			}
		}
	}
}

// middle value
string* Tree::middleString(const string first, const string second, const string data) const{
	string* middle = new string[3];
	if(data  < first ){
		middle[0] = data, middle[1] = first; middle[2] = second;
	} else if(data  > second ){
		middle[0] = first; middle[1] = second; middle[2] = data;
	} else{
		middle[0] = first; middle[1] = data; middle[2] = second;
	}
	return middle;
}

// node is parent
// three node case
Node* Tree::split(Node* node, Node* data, const int x) const{
	Node* nodeData[4];
	if(x == 0){
		nodeData[0] = data->left;
		nodeData[1] = data->right;
		nodeData[2] = node->middle;
		nodeData[3] = node->right;
	} else if(x == 2){
		nodeData[0] = node->left;
		nodeData[1] = node->middle;
		nodeData[2] = data->left;
		nodeData[3] = data->right;
	} else{
		nodeData[0] = node->left;
		nodeData[1] = data->left;
		nodeData[2] = data->right;
		nodeData[3] = node->right;
	}
	
	string* middle = middleString(node->small, node->large, data->small);
	
	Node* up = new Node(middle[1]);
	Node* newLeft = new Node(middle[0]);
	Node* newRight = new Node(middle[2]);
	
	up->left = newLeft;
	up->right = newRight;
	newLeft->parent = up;
	newRight->parent = up;
	
	if(nodeData[0]){
		newLeft->left = nodeData[0];
		newLeft->right = nodeData[1];
		
		nodeData[0]->parent = nodeData[1] = newLeft;
		
		newRight->left = nodeData[2];
		newRight->right = nodeData[3];
		
		nodeData[2] = nodeData[3] = newRight;
	}
	return up;
}

void Tree::twoNodeInsert(string data, Node* &node) const{
	if(data  < node->small ){
		node->large = node->small;
		node->small = data;
	} else{
		node->large = data;
	}
}

int Tree::nodeChild(Node* node, Node* parental) const{
	if(node == parental->left) return 0;
	else if(node == parental->middle) return 1;
	else return 2;
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