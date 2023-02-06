#include <stdio.h>
#include "hello_world.hpp"

template <typename T>
void printVector(vector<T> vector) 
{
    for (T element : vector)
    {
        cout << element << " ";
    }
    cout << endl;
};