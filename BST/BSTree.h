#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <iostream>
#include <cstdlib>
#include "Node.h"

using namespace std;

class BSTree {

  private:
    Node *root;

  private:
    void preOrder(Node * ) const;
    void inOrder(Node * ) const;
    void postOrder(Node * ) const;
    void destructor(Node* &) const;
    Node* searchNode(const string& data, Node* node) const;
    void insert(const string &, Node* & node) const;        // need &
    void remove(const string& data, Node* & node) const;    // need &
    const string smallest(Node* ) const;
    const string largest(Node* ) const;
    int height(const string& data, Node* node) const;


  public:
    BSTree();
    ~BSTree();
    void insert(const string &);
    bool search(const string &) const;
    void inOrder();
    void postOrder();
    void preOrder();
    const string largest() const;
    const string smallest() const;
    int height(const string &) const;
    void remove(const string &);
};

#endif