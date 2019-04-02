// Sabrina Wong and Xufei Wang

#include "IntList.h"

#include <iostream>
#include <cstdlib>

using namespace std;

IntList::IntList(){
    head = new IntNode(0);
    tail = new IntNode(0);
    
    head->next = tail;
    tail->prev = head;
}

IntList::~IntList(){
    IntNode* curr = head->next;
    
    while(curr != this->tail){
        delete curr;
        curr = curr->next;
    }
    
    delete head;
    delete tail;
}

void IntList::push_front(int value){
    IntNode* temp = new IntNode(value);
    
    temp->prev = head;
    temp->next = head->next;
    head->next->prev = temp;
    head->next = temp;
    
    return;
}

void IntList::push_back(int value){
    IntNode* temp = new IntNode(value);
    
    temp->next = tail;
    temp->prev = tail->prev;
    tail->prev->next = temp;
    tail->prev = temp;
    
    
    return;
}

void IntList::pop_back(){
    if(tail->prev == head){
        return;
    }
    
    else{
        tail->prev = tail->prev->prev;
        tail->prev->next = tail;
    }
}

void IntList::pop_front(){
    if(head->next == tail){
        return;
    }
    
    else{
        head->next = head->next->next;
        head->next->prev = head;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if(rhs.empty()){
        return out;
    }
    
    IntNode* curr = rhs.head->next;
    
    while(curr != rhs.tail->prev){
        out << curr->data << " ";
        curr = curr->next;
    }
    out << curr->data;
    
    return out;
}

void IntList::printReverse() const{
    if(this->empty()){
        return;
    }
    
    IntNode* curr = this->tail->prev;
    
    while(curr != this->head->next){
        cout << curr->data << " ";
        curr = curr->prev;
    }
    
    cout << curr->data;
}

bool IntList::empty() const{
    if(this->head->next == tail){
        return true;
    }
    else{
        return false;
    }
}
