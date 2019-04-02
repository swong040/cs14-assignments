// Sabrina Wong and Xufei Wang

#include <iostream>
#include <cstdlib>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList{
    IntNode* head;
    IntNode* tail;
    
public:
    IntList();
    ~IntList();

    void push_back(int);
    void push_front(int);
    
    void pop_back();
    void pop_front();
    
    friend ostream & operator<<(ostream &out, const IntList &rhs);
    void printReverse() const;
    bool empty() const;
};

