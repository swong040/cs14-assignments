#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
using namespace std;

template<typename T>
unsigned min_index(vector<T>& vals, unsigned index)
{
        unsigned minimum = index;
        for(unsigned i = index; i < vals.size(); ++i)
        {
                if(vals.at(minimum) > vals.at(i))
                {
                        minimum = i;
                }
        }
        return minimum;
}

template<typename T>
void selection_sort(vector<T> &vals)
{
        /* a[0] to a[n-1] is the array to sort */
        int j;
        int n = vals.size();
/* advance the position through the entire array */
/*   (could do j < n-1 because single element is also min element) */
        for (j = 0; j < n-1; j++) {
                /* find the min element in the unsorted a[j .. n-1] */

                /* assume the min is the first element */
                int iMin = min_index(vals,j);
                /* test against elements after j to find the smallest */
                // for ( i = j+1; i < n; i++) {
                //         /* if this element is less, then it is the new minimum */
                //         if (vals[i] < vals[iMin]) {
                //                 /* found new minimum; remember its index */
                //                 iMin = i;
                //         }
                // }

                swap(vals[j], vals[iMin]);
        }
}

vector<char> createVector()
{
        int vecSize = rand() % 26;
        char c = 'a';
        vector<char> vals;
        for(int i = 0; i < vecSize; i++)
        {
                vals.push_back(c);
                c++;
        }
        return vals;
}

char getChar(vector<char>& vals, int index)
{
  try
  {
    return vals.at(index);
  }
  catch(const std::out_of_range& e)
  {
    cout << e.what()<<endl;
  }
  return 0;
}

int main()
{
        vector<int> test;
        test.push_back(10);
        test.push_back(9);
        test.push_back(20);
        test.push_back(5);
        selection_sort(test);
        for(unsigned i =0; i < test.size(); ++i)
        {
          cout << test.at(i) << " ";
        }

        cout<<endl << min_index(test,0) << endl;
        //Part B
        srand(time(0));
        vector<char> vals = createVector();
        char curChar = 'a';
        int index;
        int numOfRuns = 5;
        while(--numOfRuns >= 0) {
                cout << "Enter a number: " << endl;
                cin >> index;
                curChar = getChar(vals,index);
                cout << curChar << endl;
        }
        return 0;
}
