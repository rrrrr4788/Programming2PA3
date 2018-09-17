#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include<string.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;


class stack {
public:
	string st[100];
	int count = 0;
	void push(string);
	string pop();
	void showup();
	bool check(string stuff);
	bool isempty();
	string onTop();
	void deleteTop();
	int numTwos();
};


bool isOperator(char character);
bool isKeyword(string word);
bool isDelimiter(char oops);
bool isParenthesis(char ah_oh);
#pragma once
