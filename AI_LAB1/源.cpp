#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<string>
#include <sstream>
using namespace std;

int To_Num(string str) {
	int num=0;
	if (str != "") {
		str = str.substr(1, str.length() - 2);
		stringstream ss(str);
		ss >> num;
	}
	return num;
}

class Sparse_Matrix_Elem {
public:
	Sparse_Matrix_Elem();
	Sparse_Matrix_Elem(int row, int col, int value);
	Sparse_Matrix_Elem(string str);
	bool operator<(Sparse_Matrix_Elem &elem);
	int row, col, value;
};

Sparse_Matrix_Elem::Sparse_Matrix_Elem()
{
	col = row = value = 0;
}

Sparse_Matrix_Elem::Sparse_Matrix_Elem(int row, int col, int value)
{
	this->col = col;
	this->row = row;
	this->value = value;
}

Sparse_Matrix_Elem::Sparse_Matrix_Elem(string str)
{
	string row="", col = "", value = "";
	int cnt = 0;
	for (int i = 0; i < str.length(); i++) {
		if (cnt == 0 && str[i] >= '0'&&str[i] <= '9') row += str[i];
		if (cnt == 1 && str[i] >= '0'&&str[i] <= '9') col += str[i];
		if (cnt == 2 && str[i] >= '0'&&str[i] <= '9') value += str[i];
		if (str[i] == ',')cnt++;
	}
	stringstream ssr(row),ssc(col),ssv(value) ;
	ssr >> this->row;
	ssc >> this->col;
	ssv >> this->value;
}

bool Sparse_Matrix_Elem::operator<(Sparse_Matrix_Elem & elem)
{
	if (this->row == elem.row) {
		return this->col < elem.col;
	}
	else return this->row < elem.row;
}

class Sparse_Matrix
{
public:
	Sparse_Matrix();
	Sparse_Matrix(int row,int col,int num);
	Sparse_Matrix operator+(Sparse_Matrix Matrix);
	Sparse_Matrix &operator+=(Sparse_Matrix &Matrix);
	friend istream& operator >>(istream &is, Sparse_Matrix &Matrix);
	friend ostream& operator <<(ostream &os, Sparse_Matrix &Matrix);
private:
	int row, col, num;
	vector<Sparse_Matrix_Elem>elem;
};

Sparse_Matrix::Sparse_Matrix()
{
	row = col = num = 0;
}
Sparse_Matrix::Sparse_Matrix(int row, int col, int num)
{
	this->row = row;
	this->col = col;
	this->num = num;
}

Sparse_Matrix Sparse_Matrix::operator+(Sparse_Matrix Matrix)
{
	int cnt = 0, i = 0, j = 0;
	vector<Sparse_Matrix_Elem>tmp;
	Sparse_Matrix_Elem temp;
	Sparse_Matrix other;
	while (cnt<this->num+Matrix.num)
	{
		if (i >= this->num) {
			tmp.push_back(Matrix.elem[j]);
			j++;
			cnt++;
		}
		else if (j >= Matrix.num) {
			tmp.push_back(this->elem[i]);
			i++;
			cnt++;
		}
		else {
			if (this->elem[i] < Matrix.elem[j]) {
				tmp.push_back(this->elem[i]);
				i++;
				cnt++;
			}
			else if (this->elem[i].col == Matrix.elem[j].col&&this->elem[i].row == Matrix.elem[j].row) {
				temp.col = this->elem[i].col;
				temp.row = this->elem[i].row;
				temp.value = this->elem[i].value + Matrix.elem[j].value;
				tmp.push_back(temp);
				i++;
				j++;
				cnt += 2;
			}
			else {
				tmp.push_back(Matrix.elem[j]);
				j++;
				cnt++;
			}
		}
	}
	other.col = max(this->col, Matrix.col);
	other.row = max(this->row, Matrix.row);
	other.elem = tmp;
	other.num = tmp.size();
	return other;
}

Sparse_Matrix & Sparse_Matrix::operator+=(Sparse_Matrix & Matrix)
{
	int cnt = 0, i = 0, j = 0;
	vector<Sparse_Matrix_Elem>tmp;
	Sparse_Matrix_Elem temp;
	Sparse_Matrix other;
	while (cnt<this->num + Matrix.num)
	{
		if (i >= this->num) {
			tmp.push_back(Matrix.elem[j]);
			j++;
			cnt++;
		}
		else if (j >= Matrix.num) {
			tmp.push_back(this->elem[i]);
			i++;
			cnt++;
		}
		else {
			if (this->elem[i] < Matrix.elem[j]) {
				tmp.push_back(this->elem[i]);
				i++;
				cnt++;
			}
			else if (this->elem[i].col == Matrix.elem[j].col&&this->elem[i].row == Matrix.elem[j].row) {
				temp.col = this->elem[i].col;
				temp.row = this->elem[i].row;
				temp.value = this->elem[i].value + Matrix.elem[j].value;
				tmp.push_back(temp);
				i++;
				j++;
				cnt += 2;
			}
			else {
				tmp.push_back(Matrix.elem[j]);
				j++;
				cnt++;
			}
		}
	}
	this->col = max(this->col,Matrix.col);
	this->row = max(this->row, Matrix.row);
	this->elem = tmp;
	this->num = tmp.size();
	return *this;
}

istream & operator>>(istream & is, Sparse_Matrix & Matrix)
{
	string row, col, num,str;
	is >> row >> col >> num;
	Matrix.row = To_Num(row);
	Matrix.col = To_Num(col);
	Matrix.num = To_Num(num);
	for (int i = 0; i < Matrix.num; i++) {
		is >> str;
		Sparse_Matrix_Elem tmp(str);
		Matrix.elem.push_back(tmp);
		if (Matrix.elem[i].row< 0 || Matrix.elem[i].row >= Matrix.row || Matrix.elem[i].col < 0 || Matrix.elem[i].col >= Matrix.col) {
			cout << "wrong\n";
			break;
		}
	}
	sort(Matrix.elem.begin(), Matrix.elem.end());
	cout << "end\n";
	return is;
}

ostream & operator<<(ostream & os, Sparse_Matrix & Matrix)
{
	os << '[' << Matrix.row << "]\n" << '[' << Matrix.col << "]\n" << '[' << Matrix.num << "]\n";
	for (int i = 0; i < Matrix.num; i++) {
		os << '[' << Matrix.elem[i].row << ',' << Matrix.elem[i].col << ',' << Matrix.elem[i].value << "]\n";
	}
	return os;
}

int main() {
	Sparse_Matrix m1,m2,m3;
	ifstream in1("M.txt");
	ifstream in2("M1.txt");
	ofstream out("M2.txt");
	ofstream out1("M3.txt");
	in1 >> m1;
	in2 >> m2;
	//cin >> m1 >> m2;
	//cout << m1 << m2;
	m3 = m1 + m2;
	out << m3;
	m1 += m2;
	m1 += m3;
	out1 << m1;
	system("pause");
}