#define _CRT_SECURE_NO_WARNINGS
#include"Sparse_Matrix.h"
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