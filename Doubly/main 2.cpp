// Sabrina Wong and Xufei Wang

#include "IntList.h"
#include <iostream>

using namespace std;

int main(){
    IntList aa;
    cout << aa << endl;
    
    aa.push_back(5);
    cout << aa << endl;
    
    aa.push_front(4);
    cout << aa << endl;
    
    aa.push_front(3);
    aa.push_front(2);
    aa.push_front(1);
    aa.push_back(6);
    aa.push_back(7);
    cout << aa << endl;
    
    aa.pop_back();
    cout << aa << endl;
    
    aa.pop_back();
    cout << aa << endl;
    
    aa.pop_front();
    cout << aa << endl;
    
    aa.pop_front();
    cout << aa << endl;
    
    aa.pop_front();
    cout << aa << endl;
    
    return 0;
}