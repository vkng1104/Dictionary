#include "HeaderS.h"

void viewQueue(queue<string> a)
{
	while (a.size() > 0)
	{
		cout << a.front() << endl;
		a.pop();
	}
}

void add(active_point* active, node* root, string a, string def)
{
	string b, c;
	int start = 0, k;
	active->node = root;
	active->length = 0;
	active->edge = '\0';
	for (int i = 0; i < a.size(); i++)
	{
		if (active->edge == '\0')
		{
			active->edge = a[i];
		}
		if (active->node->edge[int(active->edge) - 32].size() > 0 && active->node->edge[int(active->edge) - 32][active->length] == a[i])
		{
			active->length++;
			if (active->length >= active->node->edge[int(active->edge) - 32].size())
			{
				start += active->length;
				active->node = active->node->pnext[int(active->edge) - 32];
				active->length = 0;
				active->edge = '\0';
			}
		}
		else
		{
			for (k = i; k < a.size(); k++)
			{

				c += a[k];
			}
			k = i;
			break;
		}
	}
	for (int i = 0; i < active->length; i++)
	{
		b += a[start + i];
	}
	split(active, b, c, def);
}

void split(active_point* active, string b, string c, string def)
{
	//	cout<<"b:   "<<b<<"       c:      "<<c<<endl;
	if (active->length == 0)
	{
		active->node->edge[int(c[0]) - 32] += c;
		active->node->pnext[int(c[0]) - 32] = new node;
		active->node->pnext[int(c[0]) - 32]->edge[95] = "$" + def;
	}
	else if (c.size() > 0)
	{
		int loc = int(b[0]) - 32;
		string sEdge;
		node* tmp = new node;
		for (int i = active->length; i < active->node->edge[loc].size(); i++)
		{
			sEdge += active->node->edge[loc][i];
		}
		tmp->edge[int(c[0]) - 32] += c;
		tmp->pnext[int(c[0]) - 32] = new node;
		tmp->pnext[int(c[0]) - 32]->edge[95] = "$" + def;
		tmp->pnext[int(sEdge[0]) - 32] = active->node->pnext[loc];
		tmp->edge[int(sEdge[0]) - 32] = sEdge;
		active->node->pnext[loc] = tmp;
		active->node->edge[loc] = b;
	}
	else
	{
		int loc = int(b[0]) - 32;
		string sEdge;
		node* tmp = new node;
		tmp->edge[95] += "$" + def;
		for (int i = active->length; i < active->node->edge[loc].size(); i++)
		{
			sEdge += active->node->edge[loc][i];
		}
		tmp->pnext[int(sEdge[0]) - 32] = active->node->pnext[loc];
		tmp->edge[int(sEdge[0]) - 32] = sEdge;
		active->node->pnext[loc] = tmp;
		active->node->edge[loc] = b;
	}
}

void getFile(string file_name, node* root)
{
	ifstream fin;
	int x = -1, y = -1;
	fin.open(file_name + ".txt");
	gTrav(fin, root, 0, x, y);
	fin.close();
}

void gTrav(ifstream& fin, node*& cur, int gLevel, int& dLevel, int& loc)
{
	if (fin.eof()) return;
	char data[200];
	if (!cur) cur = new node;
	while (!fin.eof())
	{
		if (dLevel == -1)
		{
			fin >> dLevel;
			fin >> loc;
		}
		if (gLevel == dLevel)
		{
			fin.ignore(1);
			fin.getline(data, 199, '\n');
			cur->edge[loc] = data;
			dLevel = -1;
			if (loc < 95) gTrav(fin, cur->pnext[loc], gLevel + 1, dLevel, loc);
		}
		else if (gLevel > dLevel) return;
	}
}


void saveFile(string file_name, node* root)
{
	ofstream fout;
	fout.open(file_name + ".txt");
	sTrav(fout, root, 0);
	fout.close();
}

void sTrav(ofstream& fout, node* cur, int level)
{
	if (!cur) return;
	for (int i = 0; i < 96; i++)
	{
		if (cur->edge[i].size() > 0)
		{
			fout << level << endl;
			fout << i << endl;
			fout << cur->edge[i] << endl;
			if (i < 95) sTrav(fout, cur->pnext[i], level + 1);
		}
	}
}

bool randomQuiz(node* root, active_point* active)
{
	node* def[4];
	int t, loc = 0, decision;
	string ans, roll;
	def[0] = randomWord(root, active, ans);
	def[1] = def[0];
	t = 20;
	while (def[1] == def[0])
	{
		t--;
		def[1] = randomWord(root, active, roll);
		if (t == 0) break;
	}
	def[2] = def[0];
	t = 20;
	while (def[2] == def[1] || def[2] == def[0])
	{
		t--;
		def[2] = randomWord(root, active, roll);
		if (t == 0) break;
	}
	def[3] = def[0];
	t = 20;
	while (def[3] == def[2] || def[3] == def[1] || def[3] == def[0])
	{
		t--;
		def[3] = randomWord(root, active, roll);
		if (t == 0) break;
	}
	t = 10;
	while (t > 0)
	{
		decision = rand() % 4 + 0;
		if (loc != decision) swap(def[loc], def[decision]);
		loc = decision;
		t--;
	}

	cout << "word : " << ans << endl;
	cout << "definition choices:" << endl;
	cout << "1. ";
	for (int k = 1; k < def[0]->edge[95].size(); k++) cout << def[0]->edge[95][k];
	cout << endl;
	for (int i = 1; i < 4; i++)
	{
		cout << i + 1 << ". ";
		for (int x = 0; x < i; x++)
		{
			if (def[i] == def[x])
			{
				cout << "" << endl;
				break;
			}
			else if (x == i - 1)
			{
				for (int k = 1; k < def[i]->edge[95].size(); k++) cout << def[i]->edge[95][k];
				cout << endl;
			}
		}
	}
	cout << "your answer: ";
	cin >> decision;
	if (decision - 1 == loc) return true;
	else return false;
}

node* randomWord(node* root, active_point* active, string& word)
{
	word = "";
	if (!root) return NULL;
	int t;
	active->node = root;
	while (root)
	{
		t = rand() % 96 + 0;
		int start = t;
		while (active->node->edge[t].size() == 0)
		{
			t++;
			if (t == start) return NULL;
			if (t == 96) t = 0;
		}
		if (t == 95)
		{
			return active->node;
		}
		else
		{
			word += active->node->edge[t];
			active->node = active->node->pnext[t];
		}
	}
}

bool changeDef(node* root, string arr, active_point* active, string new_def)
{
	node* tmp = searchNode(root, arr, active);
	if (tmp == NULL) return false;
	tmp->edge[95] = "$" + new_def;
	return true;
}

node* searchNode(node* root, string arr, active_point* active)
{
	if (arr.size() == 0 || !root) return NULL;
	active->node = root;
	active->length = 1;
	active->edge = arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		if (active->length == active->node->edge[int(active->edge) - 32].size())
		{
			active->node = active->node->pnext[int(active->edge) - 32];
			active->edge = arr[i];
			active->length = 0;
		}
		if (active->node->edge[int(active->edge) - 32][active->length] == arr[i])
		{
			active->length++;
		}
		else
		{
			return NULL;
		}
	}
	if (active->length == active->node->edge[int(active->edge) - 32].size())
	{
		return active->node->pnext[int(active->edge) - 32];
	}
	else
	{
		return NULL;
	}
}

vector<string> searchWord(node* root, string arr, active_point* active)
{
    vector<string> ans;
	if (arr.size() == 0 || !root || root->edge[int(arr[0]) - 32].size() == 0)
	{
        ans.push_back("Something is wrong! We cannot find this word or any related words");
        ans.push_back("If you know that this word exists, please press +");
        return ans;
	}
	string a = "";
	active->node = root;
	active->length = 1;
	active->edge = arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		if (active->length == active->node->edge[int(active->edge) - 32].size())
		{
			a += active->node->edge[int(active->edge) - 32];
			active->node = active->node->pnext[int(active->edge) - 32];
			active->edge = arr[i];
			active->length = 0;
		}
		if (active->node->edge[int(active->edge) - 32][active->length] == arr[i])
		{
			active->length++;
		}
		else
		{
            ans.push_back("Something is wrong! We cannot find this word or any related words");
            ans.push_back("If you know that this word exists, please press +");
            return ans;
		}
	}
	a += active->node->edge[int(active->edge) - 32];
	active->node = active->node->pnext[int(active->edge) - 32];
    printall(active->node, a, ans);
    return ans;
}

void delWord(node* root, string arr, active_point*& active)
{
	if (arr.size() == 0 || !root) return;
	int t = 0, z;
	node* prev_node;

	active->node = root;
	active->length = 1;
	active->edge = arr[0];

	for (int i = 1; i < arr.size(); i++)
	{
		if (active->length == active->node->edge[int(active->edge) - 32].size())
		{
			active->node = active->node->pnext[int(active->edge) - 32];
			active->edge = arr[i];
			active->length = 0;
		}
		if (active->node->edge[int(active->edge) - 32][active->length] == arr[i]) active->length++;
		else return;
	}
	prev_node = active->node;
	active->node = active->node->pnext[int(active->edge) - 32];
	for (int i = 0; i < 95; i++)
	{
		if (active->node->pnext[i])
		{
			t++;
			z = i;
		}
	}
	if (t == 0)
	{
		delete active->node;
		prev_node->edge[int(active->edge) - 32] = "";
		prev_node->pnext[int(active->edge) - 32] = NULL;
	}
	else if (t == 1)
	{
		prev_node->edge[int(active->edge) - 32] += active->node->edge[z];
		prev_node->pnext[int(active->edge) - 32] = active->node->pnext[z];
		delete active->node;
	}
	else active->node->edge[95] = "";
}

void deltree(node* root)
{
	if (!root) return;
	for (int i = 0; i < 95; i++)
	{
		if (root->pnext[i]) deltree(root->pnext[i]);
	}
	delete root;
	root = NULL;
}

void printTree(node* root, int level)
{
	if (!root)
	{
		return;
	}
	cout << "level   :   " << level << endl;
	for (int i = 0; i < 96; i++)
	{
		if (root->edge[i].size() > 0)
		{
			cout << "edge[" << i << "]    :    " << root->edge[i] << endl;
		}
		if (i < 95 && root->pnext[i])
		{
			printTree(root->pnext[i], level + 1);
			cout << "level : " << level << endl;
		}
	}
}

void printall(node* root, string arr, vector<string> &ans)
{
    string str = "";
	if (root->edge[95][0] == '$')
    {
        for (int i = 1; i < root->edge[95].size(); i++) str+= root->edge[95][i];
        ans.push_back(arr + '\t' + str);
        // cout << endl;
    }
    if(ans.size() == 1) ans.push_back("Or you mean that/those below?");
    for (int i = 0; i < 95; i++)
    {
        if (root->pnext[i]) printall(root->pnext[i], arr + root->edge[i], ans);
    }
}
