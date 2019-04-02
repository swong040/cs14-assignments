#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

struct Node{
    string data;
    Node* left;
    Node* right;
    int count;
    Node(const string& data):data(data),left(0),right(0),count(1){}

};

#endif