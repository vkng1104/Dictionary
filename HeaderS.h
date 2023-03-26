#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;

struct node
{
	string edge[96];
	node* pnext[95] = { NULL };
};

struct active_point
{
	node* node;
	char edge;
	int length;
};

//working with file
void saveFile(string file_name, node* root);
void sTrav(ofstream& fout, node* cur, int level);
void getFile(string file_name, node* root);
void gTrav(ifstream& fin, node*& cur, int gLevel, int& dLevel, int& loc);

//working with compressed trie
void viewQueue(queue<string> a);
void add(active_point* active, node* root, string a, string def);
void split(active_point* active, string b, string c, string def);
void deltree(node* root);
void printTree(node* root, int level);                      //print all edges and their depth
void printall(node* root, string arr, vector<string>& ans);	//print all words and their definitions
void delWord(node* root, string arr, active_point*& active);
vector<string> searchWord(node* root, string arr, active_point* active);
node* searchNode(node* root, string arr, active_point* active);
bool changeDef(node* root, string arr, active_point* active, string new_def);
node* randomWord(node* root, active_point* active, string& word);
bool randomQuiz(node* root, active_point* active);
