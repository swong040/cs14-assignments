#ifndef JUG_H
#define JUG_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include <stack>
#include <sstream>
#include <algorithm>


using namespace std;



class Map{
    public:
        pair<int,int> first;
        int second; // index
        
        Map(pair<int,int> first, int index): first(first), second(index){}
};

class Store{
    public:
        pair<int,int> jugs;
        int cost;
        int totalCost;
        int done;
        Store* prev;
        Store* next;
        bool fA, fB, eA, eB, pAB, pBA;
        
        Store():  cost(0), totalCost(0), done(0),prev(NULL), next(NULL), fA(false), fB(false), eA(false), eB(false), pAB(false), pBA(false){}
        Store(pair<int, int> jugs, int cost, int done): jugs(jugs), cost(cost), totalCost(0), done(done),
              prev(NULL), next(NULL), fA(false), fB(false), eA(false), eB(false), pAB(false), pBA(false){}

        bool operator<(const Store& rhs) const{ 
            return totalCost < rhs.totalCost; 
        }  
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug(){}


        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        int A, B;
        vector<list<Store> > start;
        vector<Map> graph;
        
        void fill_A();
        void fill_B();
        void empty_A();
        void empty_B();
        void pour_AB();
        void pour_BA();
        void fillMap();
        int mapIndex(Store u);
};

#endif