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

int _tmain(int argc, _TCHAR* argv[]){
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	_getch();
	return 0;
}
