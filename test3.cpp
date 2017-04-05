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

	bool readPasswFile(string s) {
		try {
			ifstream ifs(s);
			if (ifs.is_open()) {
				int n;
				ifs >> n;
				int u;
				for (int i = 0; i < n; i++) {
					ifs >> u;
					code.push_back(u);
				}
				return true;
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

int _tmain(int argc, _TCHAR* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	_getch();
	return 0;
}
