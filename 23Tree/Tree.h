#ifndef __TREE_H
#define __TREE_H

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

class Tree {
  private:
    Node *root;

  public:
    Tree( );
    ~Tree( );
    void insert(const string & data);
    void preOrder( );
    void inOrder( );
    void postOrder( );
    void remove(const string &);
    bool search (const string &);

    void visualizeTree(const string &outputFilename);

  private:
  
    // Add additional functions/variables here
    bool isLeaf(Node* node) const;
    bool twoNode(Node* node) const;
    bool threeNode(Node* node) const;

    void preOrder(Node* );
    void inOrder(Node* );
    void postOrder(Node* );
  
    Node* searchNode(const string &, Node* ) const;

    void insert(const string & data, Node* & node) const;
    Node* split(Node* node, Node* data, const int x) const;
    void twoNodeInsert(string data, Node* &node) const;
    string* middleString(const string first, const string second, const string data) const;
    int nodeChild(Node* node, Node* parental) const;

    void visualizeTree(ofstream & outFS, Node *n);

};

#endif