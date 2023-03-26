#pragma once



#include <iostream>
#include<fstream>
#include<vector>
#include <string>
#include <cctype>
#include <codecvt>
#include <locale>

using namespace std;

const int ALPHABET_SIZE = 128;

struct Node2 //eng eng
{
	Node2* child[ALPHABET_SIZE];
	string form;
	string meaning;
	bool EndOfWord;

};

//Eng Eng

Node2* getNode2();

void insert2(Node2*& root, string& key, string& meaning, string& form);
string GetMeaning2(Node2*& root, string& key);
void Input2(Node2*& root);
bool isEmpty(Node2*& root);

void Add(Node2*& root);

void Editdef(Node2*& root, string& key);
void EditDefhelp(Node2*& root, string& key, string& meaning);
void EditOut(Node2*& root, string& str);

Node2* deleteWordHelper(Node2* root, string& key, int depth);
Node2* deleteWord(Node2*& root, string& key);
void Del(Node2*& root, string& key);
void DelOut(Node2*& root, string& str);

void Restart(Node2*& root);

void InputHistory();
void InputFav();