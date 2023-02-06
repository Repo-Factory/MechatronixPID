#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
void printVector(vector<T> vector);

template <typename T>
vector<T>& operator-=(vector<T> &lhs, const vector<T> &rhs);

template <typename T>
vector<T> operator- (vector<T> lhs, const vector<T> &rhs);

template <typename T>
vector<T>& operator+=(vector<T> &lhs, const vector<T> &rhs);

template <typename T>
vector<T> operator+ (vector<T> lhs, const vector<T> &rhs);

template <typename T>
vector<T> operator-(vector<T> lhs, const T &rhs);

template <typename T>
vector<T> operator+(vector<T> lhs, const T &rhs);

template <typename T>
bool operator<(vector<T> lhs, const T &rhs);

template <typename T>
bool operator>(vector<T> lhs, const T &rhs);

template <typename T>
vector<T> operator*(vector<T> lhs, const T &rhs);

template<typename T>
vector<T> operator*(vector<vector<T>> lhs, const vector<T> &rhs);