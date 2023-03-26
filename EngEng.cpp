#include "Header.h"

Node2* getNode2()
{
	Node2* pNode = new Node2();

	pNode->EndOfWord= false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->child[i] = NULL;

	return pNode;
}
void insert2(Node2*& root, string& key, string& meaning, string& form)    //Eng-Eng
{

	if (root == NULL)
	{
		root = getNode2();
	}

	Node2* cur = root;
	for (int i = 0; i < key.length(); i++)
	{
		
		if (cur->child[key[i]] == NULL)
		{
			cur->child[key[i]] = getNode2();
		}
		cur = cur->child[key[i]];
	}
	cur->EndOfWord= true;
	cur->meaning = meaning;
	cur->form = form;

}

void Add(Node2*& root)
{
	string key, meaning, form;

	cout << "Enter the word: ";
	cin >> key;
	cout << "Enter the form of the word: ";
	getline(cin, form, '\n');
	cout << "Enter the meaning: ";
	getline(cin, form, '\n');
	insert2(root, key, meaning, form);
}
string GetMeaning2(Node2*& root, string& key)
{
	Node2* cur = root;
	if (root == NULL)
	{
		return "Fail";
	}

	for (int i = 0; i < key.length(); i++)
	{

	
		cur = cur->child[key[i]];
		if (cur == NULL)
		{
			cout << "Fail";
			return "Fail";
		}


	}
	cout << "The Word meaning: ";
	cout <<cur->form<<" "<< cur->meaning;
	return cur->meaning;
}
Node2* Search(Node2*& root, string& key)
{
	Node2* cur = root;
	if (root == NULL)
	{
		cout << "fail";
		return NULL;
	}

	for (int i = 0; i < key.length(); i++)
	{


		cur = cur->child[key[i]];
		if (cur == NULL)
		{
			cout << "Fail";
			return NULL;
		}


	}
	
	return cur;
}
void EditDef(Node2*& root, string& key)
{
	
	Node2* cur= Search(root, key);
	cout <<"The current defintion: "<< cur->meaning << endl;
	string str;
	getline(cin, str, '\n');
	

}
void Input2(Node2*& root) 
{
	ifstream fin;
	fin.open("EngEngraw.txt");
	int i = 0;
	string str;

	if (fin.is_open())
	{
		while (fin)
		{
			string str2;
			string meaning;
			string form;
			fin >> str2;
			
			getline(fin, form, ' ');
			getline(fin, meaning, '\n');
			insert2(root, str2, meaning, form);
		}

	}
	else
		cout << "fail";
	fin.close();
}
bool isEmpty(Node2* &root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->child[i])
			return false;
	return true;
}

Node2* deleteWordHelper(Node2* root, string& key, int depth)
{
	if (root == NULL) {
		return NULL;
	}

	if (depth == key.length())
	{                   

		if (root->EndOfWord)
		{
			root->EndOfWord = false;               
		}

		if (isEmpty(root))
		{                    
			root = nullptr;
		}

		return root;
	}

	           

	root->child[key[depth]] = deleteWordHelper(root->child[key[depth]+1], key, depth + 1); //Recursive call

	if (isEmpty(root) && root->EndOfWord == false)
	{
		root = nullptr;
	}

	return root;
}


Node2* deleteWord(Node2*& root, string& key)
{
	int depth = 0;                              
	return deleteWordHelper(root,key, depth);    

}


