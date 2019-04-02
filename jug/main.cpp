#include "Jug.h"

using namespace std;

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

int main(){
    {
       string solution;
       Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
       if (head.solve(solution) != 1) {
          cout << "Error 3" << endl;
       }
       cout << solution << endl << endl;
    }
    {
      string solution;
      Jug tail( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
      if(tail.solve(solution) != 1) {
          cout << "Error 3" << endl;
      }
      cout << solution << endl;
    }
    return 0;
}

// g++ -o a.out main.cpp Jug.cpp; ./a.out