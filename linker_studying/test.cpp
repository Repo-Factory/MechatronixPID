#include "vector_operations.hpp"

vector<double> a{3.0,5.0,7.0};

vector<double> b{2.0,4.0,6.0};

vector<vector<double>> c  {
                            {1.0,2.0,3.0},
                            {4.0,5.0,6.0},
                            {7.0,8.0,9.0},
                          };



vector<double> d = a  - b;
vector<double> e = a  + b;
bool f = a < b;
bool g = a > b;
vector<double> h = c * b;


int main()
{
    printVector(a);
    printVector(b);
    
    printVector(d);
    printVector(e);
    cout << f;
    cout << g;
    printVector(h);
    return 0;
}