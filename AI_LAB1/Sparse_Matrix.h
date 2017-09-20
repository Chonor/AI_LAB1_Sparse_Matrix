#pragma once
#ifndef SPARSE_MARTIX_H
#define SPARSE_MARTIX_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<string>
#include <sstream>
using namespace std;

int To_Num(string str); 

class Sparse_Matrix_Elem {
public:
	Sparse_Matrix_Elem();
	Sparse_Matrix_Elem(int row, int col, int value);
	Sparse_Matrix_Elem(string str);
	bool operator<(Sparse_Matrix_Elem &elem);
	int row, col, value;
};

class Sparse_Matrix
{
public:
	Sparse_Matrix();
	Sparse_Matrix(int row, int col, int num);
	Sparse_Matrix operator+(Sparse_Matrix Matrix);
	Sparse_Matrix &operator+=(Sparse_Matrix &Matrix);
	friend istream& operator >>(istream &is, Sparse_Matrix &Matrix);
	friend ostream& operator <<(ostream &os, Sparse_Matrix &Matrix);
private:
	int row, col, num;
	vector<Sparse_Matrix_Elem>elem;
};

#endif // !SPARSE_MARTIX_H
