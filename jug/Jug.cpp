#include "Jug.h"

using namespace std;
// notes
// { (Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA)
// Ca and Cb are the capacities of the jugs A and B
// N is the goal
// cfA is the cost to fill A
// cfB is the cost to fill B
// ceA is the cost to empty A
// ceB is the cost to empty B
// cpAB is the cost to pour A to B
// cpBA is the cost to pour B to A

// A solution is a sequence of steps that leaves jug A empty,
// and exactly N gallons in jug B. }


int Jug::solve(string& solution){
    if(0 < Ca && Ca <= Cb && N <= Cb && Cb <= 1000){
        pair<int, int> goal(0, N);
        bool yes = false;
        for(unsigned i = 0; i < start.size(); i++){
            if(start.at(i).front().jugs.first == goal.first && start.at(i).front().jugs.second == goal.second){
                yes = true;
            }
        } if(!yes){ solution = ""; return 0; }
    
        for(unsigned i = 0; i < start.size(); i++){
            start.at(i).front().totalCost = INT_MAX;
            start.at(i).front().done = 0;
            start.at(i).front().prev = NULL;
            start.at(i).front().next = NULL;
        }
        start.at(0).front().totalCost = 0;
        // g is graph (vector down)
        // w is cost - in each vector
        // s is start v(0)
        
        stack<Store> cloud;
        list<Store> lists;
        for(unsigned i = 0; i < start.size(); i++){
            lists.push_back(start.at(i).front());
        }
        while(!lists.empty()){
            lists.sort();
            Store* u = &lists.front();
            lists.pop_front();
            int index = mapIndex(*u);
            for(list<Store>::iterator it = start.at(index).begin(); it != start.at(index).end(); it++){
                int v = mapIndex(*it);
                if(start.at(v).front().totalCost > u->totalCost + it->cost){
                    start.at(v).front().totalCost = u->totalCost + it->cost;
                    start.at(v).front().done = it->done;
                    start.at(v).front().prev = u;
                    u->next = &start.at(v).front();
                    cloud.push(*u);
                   for(list<Store>::iterator yikes = lists.begin(); yikes != lists.end(); yikes++){
                        if(yikes->jugs.first == start.at(v).front().jugs.first && yikes->jugs.second == start.at(v).front().jugs.second){
                            yikes->totalCost = start.at(v).front().totalCost;
                            yikes->done = start.at(v).front().done;
                            yikes->prev = u;
                        }
                    }
                }
            }
                // if(lists.front().totalCost - u.totalCost == cfA){
                //     solution += "fill A\n";
                // } else if(lists.front().totalCost - u.totalCost == cfB){
                //     solution += "fill B\n";
                // } else if(lists.front().totalCost - u.totalCost == ceA){
                //     solution += "empty A\n";
                // } else if(lists.front().totalCost - u.totalCost == ceB){
                //     solution += "empty B\n";
                // } else if(lists.front().totalCost - u.totalCost == cpAB){
                //     solution += "pour A B\n";
                // } else if(lists.front().totalCost - u.totalCost == cpBA){
                //     solution += "pour B A\n";
                // } 
        }
        
        int index; for(unsigned i = 0; i < graph.size(); i++){
            if(graph[i].first.first == goal.first && graph[i].first.second == goal.second){
                index = graph[i].second;
            }
        } int tCost = start.at(index).front().totalCost;
        
        int count = tCost;
        Store* fuck = &start.at(index).front();
        stack<int> print;
        while(fuck != NULL){
            // cout << fuck->totalCost << endl;
            // print.push(count - fuck->totalCost);
            print.push(fuck->done);
            count -= (count - fuck->totalCost);
            fuck = fuck->prev;
        }
        
        while(!print.empty()){
            if(print.top() == 1){
                solution += "fill A\n";
            } else if(print.top() == 2){
                solution += "fill B\n";
            } else if(print.top() == 3){
                solution += "empty A\n";
            } else if(print.top() == 4){
                solution += "empty B\n";
            } else if(print.top() == 5){
                solution += "pour A B\n";
            } else if(print.top() == 6){
                solution += "pour B A\n";
            } 
            print.pop();
        }
    
        
        stringstream ss;
        ss << tCost;
        solution += "success " + ss.str();
    
        return 1;
    
    } else{
        solution = "";
        return -1;
    }
}

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA){
    A = 0; B = 0;
    if(0 < Ca && Ca <= Cb && N <= Cb && Cb <= 1000){
        this->Ca = Ca; this->Cb = Cb; this->N = N; 
        this->cfA = cfA; this->cfB = cfB; this->ceA = ceA;
        this->ceB = ceB; this->cpAB = cpAB; this->cpBA = cpBA;
    } 
    else return;

    // vector (start) of list (action) of pairs(jugs) and cost
    pair<int,int> pairs(A,B);
    Store one(pairs, 0, 0);
    list<Store> first; first.push_back(one);
    start.push_back(first);
    
    // cout << start.at(0).front().jugs.first << "," << start.at(0).front().jugs.second << endl;
    bool inGraph = false;
    unsigned i = 0;
    
    while(i < start.size()){
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        fill_A();
        if(A != start.at(i).front().jugs.first){
            pair<int, int> add(A, B);
            Store next(add, cfA, 1);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        fill_B();
        if(B != start.at(i).front().jugs.second ){
            pair<int, int> add(A, B);
            Store next(add, cfB, 2);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        empty_A();
        if(A != start.at(i).front().jugs.first){
            pair<int, int> add(A, B);
            Store next(add, ceA, 3);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        empty_B();
        if(B != start.at(i).front().jugs.second ){
            pair<int, int> add(A, B);
            Store next(add, ceB, 4);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        pour_AB();
        if(B != start.at(i).front().jugs.second){
            pair<int, int> add(A, B);
            Store next(add, cpAB, 5);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        
        A = start.at(i).front().jugs.first; B = start.at(i).front().jugs.second;
        pour_BA();
        if(A != start.at(i).front().jugs.first){
            pair<int, int> add(A, B);
            Store next(add, cpBA, 6);
            start.at(i).push_back(next);
            
            inGraph = false;
            for(unsigned j = 0; j < start.size(); j++){
                if(add.first == start.at(j).front().jugs.first && add.second == start.at(j).front().jugs.second){
                    inGraph = true;
                }
            }
            if(inGraph == false){
                list<Store> newSpot;
                next.cost = 0;
                newSpot.push_back(next);
                start.push_back(newSpot);
            }
        }
        i++;
    }
    
    fillMap();
    
    // for(unsigned i = 0; i < start.size(); i++){
    //     list<Store>::iterator it = start.at(i).begin();
    //     cout << it->jugs.first << "," << it->jugs.second;;
    //     for(it++; it != start.at(i).end(); it++){
    //         cout << " -> " << it->jugs.first << "," << it->jugs.second;
    //         cout << "(c: " << it->cost << ", tc: " << it->totalCost << ")";
    //     }
    //     cout << endl;
    // } cout << endl;
}

void Jug::fillMap(){
    for(unsigned i = 0; i < start.size(); i++){
        Map yes(start.at(i).front().jugs, i);
        graph.push_back(yes);
    }
    // for(int i = 0; i < graph.size(); i++){
    //     cout << "pair: " << graph[i].first.first << "," << graph[i].first.second << " index: " << graph[i].second << endl;
    // }
}

int Jug::mapIndex(Store u){
    int index;
    for(unsigned i = 0; i < graph.size(); i++){
        if(graph[i].first.first == u.jugs.first && graph[i].first.second == u.jugs.second){
            index = graph[i].second;
        }
    }
    return index;
}

void Jug::fill_A(){
    if(A == Ca) return;
    A = Ca;
}

void Jug::fill_B(){
    if(B == Cb) return;
    B = Cb;
}

void Jug::empty_A(){
    if(A == 0) return;
    A = 0;
}

void Jug::empty_B(){
    if(B == 0) return;
    B = 0;
}

void Jug::pour_AB(){
    if(A == 0 || B == Cb) return;
    if(A <= Ca && B < Cb){
        if(A + B > Cb){
            A = A - (Cb - B);
            B = B + (Cb - B);
        } else if(A + B <= Cb){
            B = A + B;
            A -= A;
        }
    }
}

void Jug::pour_BA(){
    if(B == 0 || A == Ca) return;
    if(A < Ca && B <= Cb){
        if(A + B > Ca){
            B = B - (Ca - A);
            A = A + (Ca - A);
        } else if(A + B <= Ca){
            A = A + B;
            B -= B;
        }
    }
}
