#include "arithmeticExpression.h"
#include <string>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

arithmeticExpression::arithmeticExpression(const string & infExpression){
    infixExpression = infExpression;
    root = 0;
}

/* Converts the infixExpression to its equivalent postfix string
   and then generates the tree and assigns the root node to the 
   root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree(){
    string post = infix_to_postfix();
    stack<TreeNode*> tree;
    char key = 'a';
    for(string::iterator it = post.begin(); it != post.end(); it++){
        if(*it == '+' || *it == '-' || *it == '*' || *it == '/'){ //c is an operator
            root = new TreeNode(*it, key);
            key++;
            root->right = tree.top();
            tree.pop();
            root->left = tree.top();
            tree.pop();
            tree.push(root);
        } else{
            TreeNode* operandNode = new TreeNode(*it, key);
            key++;
            tree.push(operandNode);
        }
    }
}

/* Calls the recursive infix function. */
void arithmeticExpression::infix(){
    infix(root);
}

void arithmeticExpression::prefix(){
    prefix(root);
}

void arithmeticExpression::postfix(){
    postfix(root);
}


void arithmeticExpression::infix(TreeNode *node){
    if (!node) return;
    
    if (node->left && node->right) cout << "(";
    
    infix(node->left);
    cout << node->data;
    infix(node->right);
    
    if (node->left && node->right) cout << ")"; 
    
}

void arithmeticExpression::prefix(TreeNode *node){
    if (!node) return;
    
    cout << node->data;
    prefix(node->left);
    prefix(node->right);
}

void arithmeticExpression::postfix(TreeNode *node){
    if (!node) return;
    
    postfix(node->left);
    postfix(node->right);
    cout << node->data;
}

/* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode * root){
    if(!root) return;
    
    visualizeTree(outFS, root->left);
    visualizeTree(outFS, root->right);
    outFS << root->key << " [label = \"" << root->data << "\"];" << endl;
    if(root->left) outFS << root->key << " -> " << root->left->key << endl;
    if(root->right) outFS << root->key << " -> " << root->right->key << endl;
}