/**
@file 5vmat.cpp
*/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale.h>
#include <math.h>
#include<list>
#include <conio.h>
#include "gtest/gtest.h"
using namespace std;


class XO {
public:
	vector<int> code;
	int **field;

	//конструктор
	//+
	XO() {
		field = new int*[3];
		for (int i = 0; i<3; i++)
			field[i] = new int[3];
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				field[i][j] = 0;
			}
	}

	//вертикальная координата из номера
	//+
	int getVert(int n) { return (n - 1) / 3; }
	//горизонтальная координата из номера
	int getHoriz(int n) { return (n - 1) % 3; }

	bool isCorrectCode() {
		if (field[0][0] == field[0][1] && field[0][1] == field[0][2] && field[0][2] == 1) return true;
		if (field[1][0] == field[1][1] && field[1][1] == field[1][2] && field[1][2] == 1) return true;
		if (field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][2] == 1) return true;
		if (field[0][0] == field[1][0] && field[1][0] == field[2][0] && field[2][0] == 1) return true;
		if (field[0][1] == field[1][2] && field[1][2] == field[2][2] && field[2][2] == 1) return true;
		if (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[2][2] == 1) return true;
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2] == 1) return true;
		if (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[2][0] == 1) return true;
		return false;
	}

	bool isCorrectPlace(int u) {
		int v = getVert(u);
		int h = getHoriz(u);
		if (field[v][h] != 0) return 0;
		return 1;
	}

	//проверка, достаточно ли крестиков-ноликов для ввода кода. 0 - хватит, 1 - надо еще
	//+
	bool notEndCycle() {
		if (code.size() == 9) return false;
		if (field[0][0] == field[0][1] && field[0][1] == field[0][2] && field[0][2]) return false;
		if (field[1][0] == field[1][1] && field[1][1] == field[1][2] && field[1][2]) return false;
		if (field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][2]) return false;
		if (field[0][0] == field[1][0] && field[1][0] == field[2][0] && field[2][0]) return false;
		if (field[0][1] == field[1][2] && field[1][2] == field[2][2] && field[2][2]) return false;
		if (field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[2][2]) return false;
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2]) return false;
		if (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[2][0]) return false;
		return true;
	}

	bool readPasswFile(string s) {
		bool f1 = true, f2 = true;
		try {
			ifstream ifs(s);
			if (ifs.is_open()) {
				int n;
				ifs >> n;
				if (n < 5 || n > 9) f1 = false;
				int u;
				for (int i = 0; i < n; i++) {
					ifs >> u;
					if (u > 9 || u < 1) f2 = false;
					code.push_back(u);
				}
				if (f1 && f2) return true;
				else return false;
			}
			else {
				return false;
			}
		}
		catch (...) {
			//что-то пошло не так
			return 0;
		}
	}
};

class MyAcc {
public:
	string myPassword;
	string myAccName;
};

class Prog {
public:
	vector <MyAcc> accounts;
	XO password;

	bool printAccounts() {
		cout << "LIST OF ACCOUNTS" << endl << endl;
		int y = 0;
		for (vector<MyAcc>::iterator r = accounts.begin(); r != accounts.end(); r++, y++)
			cout << y + 1 << ")	" << r->myAccName << "	" << r->myPassword << endl;
		return bool(y);
	}

	bool readListFile(string s) {
		bool f1 = true, f2 = true;
		try {
			ifstream ifs(s);
			if (ifs.is_open()) {
				int n;
				ifs >> n;
				if (n < 0) f1 = false;
				for (int i = 0; i < n; i++) {
					MyAcc a;
					ifs >> a.myAccName;
					ifs >> a.myPassword;
					if (a.myAccName == "" || a.myPassword == "")
						f2 = false;
					else accounts.push_back(a);
				}
				if (f1 && f2) return true;
				else return false;
			}
			else {
				return false;
			}
		}
		catch (...) {
			//что-то пошло не так
			return false;
		}
	}
};

TEST(readPasswFileTest, Test1) {
	Prog p;
	string s = "passw1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		ofs << "5 1 2 4 5 7";
	}
	ofs.close();

	ASSERT_TRUE(p.password.readPasswFile(s));
}

TEST(readPasswFileTest, Test2) {
	Prog p;
	string s = "passw1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		ofs << "1000 8 7 6 4";
	}
	ofs.close();
	//на пустой файл реакция
	ASSERT_FALSE(p.password.readPasswFile(s));
}

TEST(readPasswFileTest, Test3) {
	Prog p;
	string s = "passw1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		//запись числа без ничего
		ofs << "6 -10 -5 100 11 4 5";
	}
	ofs.close();

	ASSERT_FALSE(p.password.readPasswFile(s));
}

TEST(readListFileTest, Test1) {
	Prog p;
	string s = "mylist1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		ofs << "2 komp komp13 vkontakte qwerty";
	}
	ofs.close();

	ASSERT_TRUE(p.readListFile(s));
}

TEST(readListFileTest, Test2) {
	Prog p;
	string s = "mylist1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		ofs << "";
	}
	ofs.close();

	ASSERT_FALSE(p.readListFile(s));
}

TEST(readListFileTest, Test3) {
	Prog p;
	string s = "mylist1.txt";
	ofstream ofs(s);
	if (ofs.is_open()) {
		//запись числа без ничего
		ofs << "100 q q";
	}
	ofs.close();

	ASSERT_FALSE(p.readListFile(s));
}

TEST(XOTest, Test1) {
	XO P;
	ASSERT_FALSE(P.field[0][0]);
}

TEST(XOTest, Test2) {
	XO P;
	ASSERT_FALSE(P.field[1][0]);
}

TEST(XOTest, Test3) {
	XO P;
	ASSERT_FALSE(P.field[2][2]);
}

TEST(getVertTest, Test1) {
	XO P;
	ASSERT_EQ(0, P.getVert(1));
}

TEST(getVertTest, Test2) {
	XO P;
	ASSERT_EQ(1, P.getVert(6));
}

TEST(getVertTest, Test3) {
	XO P;
	ASSERT_EQ(0, P.getVert(2));
}

TEST(getHorizTest, Test1) {
	XO P;
	ASSERT_EQ(0, P.getHoriz(1));
}

TEST(getHorizTest, Test2) {
	XO P;
	ASSERT_EQ(2, P.getHoriz(6));
}

TEST(getHorizTest, Test3) {
	XO P;
	ASSERT_EQ(2, P.getHoriz(9));
}

TEST(isCorrectPlaceTest, Test1) {
	XO P;
	ASSERT_TRUE(P.isCorrectPlace(1));
}

TEST(isCorrectPlaceTest, Test2) {
	XO P;
	P.field[P.getVert(3)][P.getHoriz(3)] = 2;
	ASSERT_FALSE(P.isCorrectPlace(3));
}

TEST(isCorrectPlaceTest, Test3) {
	XO P;
	P.field[P.getVert(5)][P.getHoriz(5)] = 1;
	ASSERT_FALSE(P.isCorrectPlace(5));
}

TEST(notEndTest, Test3) {
	XO P;
	//O X X
	//
	//
	P.field[0][0] = 2;
	P.field[0][1] = 1;
	P.field[0][2] = 1;
	P.field[1][0] = 0;
	P.field[1][1] = 0;
	P.field[1][2] = 0;
	P.field[2][0] = 0;
	P.field[2][1] = 0;
	P.field[2][2] = 0;

	ASSERT_EQ(true, P.notEndCycle());
}

TEST(notEndTest, Test2) {
	XO P;
	//X O X
	//X O O
	//O X X
	P.code.push_back(1);
	P.code.push_back(2);
	P.code.push_back(1);
	P.code.push_back(1);
	P.code.push_back(2);
	P.code.push_back(2);
	P.code.push_back(2);
	P.code.push_back(1);
	P.code.push_back(1);

	P.field[0][0] = 1;
	P.field[0][1] = 2;
	P.field[0][2] = 1;
	P.field[1][0] = 1;
	P.field[1][1] = 2;
	P.field[1][2] = 2;
	P.field[2][0] = 2;
	P.field[2][1] = 1;
	P.field[2][2] = 1;

	ASSERT_EQ(false, P.notEndCycle());
}

TEST(notEndTest, Test1) {
	XO P;
	//X X X
	//O   O
	//  O
	P.field[0][0] = 1;
	P.field[0][1] = 1;
	P.field[0][2] = 1;
	P.field[1][0] = 2;
	P.field[1][1] = 0;
	P.field[1][2] = 2;
	P.field[2][0] = 0;
	P.field[2][1] = 2;
	P.field[2][2] = 0;

	ASSERT_EQ(0, P.notEndCycle());
}

TEST(notEndTest, Test4) {
	XO P;
	//O X X
	//  O  
	//X   O
	P.field[0][0] = 2;
	P.field[0][1] = 1;
	P.field[0][2] = 1;
	P.field[1][0] = 0;
	P.field[1][1] = 2;
	P.field[1][2] = 0;
	P.field[2][0] = 1;
	P.field[2][1] = 0;
	P.field[2][2] = 2;

	ASSERT_EQ(0, P.notEndCycle());
}

TEST(isCorrectCodeTest, Test1) {
	XO P;
	//O O O
	//  X
	//X   X
	P.field[0][0] = P.field[0][1] = P.field[0][2] = 2;
	P.field[1][0] = P.field[2][1] = P.field[2][2] = 0;
	P.field[2][0] = P.field[2][2] = P.field[1][1] = 1;
	ASSERT_FALSE(P.isCorrectCode());
}

TEST(isCorrectCodeTest, Test2) {
	XO P;
	//X X X
	//  O
	//O   O
	P.field[0][0] = P.field[0][1] = P.field[0][2] = 1;
	P.field[1][0] = P.field[2][1] = P.field[2][2] = 0;
	P.field[2][0] = P.field[2][2] = P.field[1][1] = 2;
	ASSERT_TRUE(P.isCorrectCode());
}

TEST(isCorrectCodeTest, Test3) {
	XO P;
	//X   O
	//  X
	//O   X
	P.field[0][0] = P.field[1][1] = P.field[2][2] = 1;
	P.field[1][0] = P.field[0][1] = P.field[1][2] = P.field[2][1] = 0;
	P.field[2][0] = P.field[0][2] = 2;
	ASSERT_TRUE(P.isCorrectCode());
}

TEST(printAccountsTest, Test1) {
	Prog P;
	MyAcc ma;
	ma.myAccName = "abc";
	ma.myPassword = "cde";
	P.accounts.push_back(ma);

	ASSERT_TRUE(P.printAccounts());
}

TEST(printAccountsTest, Test2) {
	Prog P;
	ASSERT_FALSE(P.printAccounts());
}

int _tmain(int argc, _TCHAR* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	_getch();
	return 0;
}
