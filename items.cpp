#include "items.h"

using namespace std;

int other(char x)
{
	int sz = 6; // size of others
	for (int i = 0; i < sz; i++)
		if (x == others[i]) return 26 + i;
	return -1;
}

nTrie::nTrie()
{
	end = false;
	definition[0] = definition[1] = definition[2] = "";
	fill(next, next + MAX, nullptr);
}
bool nTrie::empty()
{
	for (int i = 0; i < MAX; i++)
		if (next[i])
			return false;
	return true;
}

Trie::Trie()
{
	root = new nTrie();
}

void Trie::add(string s, string meaning, string phonetic, string type)
{
	int n = s.length();
	nTrie* tmp = root;
	for (int i = 0; i < n; i++)
	{
		int c;
		if (('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z'))
			c = tolower(s[i]) - 'a';
		else c = other(s[i]);
		if (!tmp->next[c])
			tmp->next[c] = new nTrie();
		tmp = tmp->next[c];
    }
	tmp->end = true;

	int k = -1;
	if (type == "English")
		k = 0;
	else
		k = 1;

	string sub = "";
    sub.push_back(char(92)); // '\n'
    sub.push_back('n');
    if (tmp->definition[k].empty())
        tmp->definition[k] += meaning;
    else tmp->definition[k] += sub + meaning;

	tmp->definition[2] += phonetic + sub;
    return;
}

string Trie::edit(string s, string meaning, string phonetic, string type)
{
    int n = s.length();
    nTrie* tmp = root;
    for (int i = 0; i < n; i++)
    {
        int c;
        if (('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z'))
            c = tolower(s[i]) - 'a';
        else c = other(s[i]);
        if (!tmp->next[c])
            return "Something is wrong, this word does NOT exist in our dictionary!";
        tmp = tmp->next[c];
    }
    if(!tmp->end) return "Something is wrong, this word does NOT exist in our dictionary!";

    int k = -1;
    if (type == "English")
        k = 0;
    else
        k = 1;

    tmp->definition[k] = meaning;
    return "Succesfully edit the definition";
}

bool Trie::toRemove(nTrie* f_root, string s, int level, int len) // len = s.length()
{
	if (!f_root)
		return false;

	if (level == len)
	{
		if (f_root->end)
		{
			f_root->end = false;
			return true;
		}
		return false;
	}

	int c;
	if (('A' <= s[level] and s[level] <= 'Z') or ('a' <= s[level] and s[level] <= 'z'))
		c = tolower(s[level]) - 'a';
	else c = other(s[level]);
	if (!f_root->next[c])
		return false;
	bool flag = toRemove(f_root->next[c], s, level + 1, len);
	if (flag && !f_root->next[c]->end && f_root->next[c]->empty())
	{
		delete f_root->next[c];
		f_root->next[c] = NULL;
	}
	return flag;
}

string Trie::remove(string s)
{
	bool fl = toRemove(root, s, 0, (int)s.length());
    if (fl) return "Successfully remove the word";
    else return (s + " was NOT FOUND in the dataset");
}

bool Trie::find(string s, vector<string>& related)
{
	if (!root)
		return false;
	string res = "";
	int n = s.length();
	nTrie* tmp = root;
	for (int i = 0; i < n; i++)
	{
		int c;
		if (('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z'))
			c = tolower(s[i]) - 'a';
		else c = other(s[i]);
		if (!tmp->next[c])
			return false;
		tmp = tmp->next[c];

		if (('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z'))
			res.push_back(tolower(s[i]));
		else res.push_back(s[i]);

		if (tmp->end)
			related.push_back(res);
	}
	if (tmp->end)
	{
		related.push_back(tmp->definition[0]);
		related.push_back(tmp->definition[1]);
		related.push_back(tmp->definition[2]);
	}
	else
	{
		continue_to_search(tmp, related, res);
	}
	return tmp->end;
}

vector<string> Trie::search(string s, bool fl1, bool fl2) // search a word
{
    vector<string> related, ans;
    bool flag = find(s, related);
    int sz = related.size(); // if flag = true then sz - 1: phonetic      sz - 2: Viet         sz - 3: Eng
	if (flag)
	{
        if (related[sz - 1].empty()) ans.push_back("No phonetic");
        else meaning(related[sz - 1], ans);

        if(fl1 and fl2)
        {
            if (related[sz - 2].empty())
                ans.push_back("No Vietnamese meaning");
            else
            {
                ans.push_back("VIETNAMESE MEANING\n");
                meaning(related[sz - 2], ans);
            }

            if (related[sz - 3].empty())
            {
                ans.push_back("No English meaning");
            }
            else
            {
                ans.push_back("ENGLISH MEANING\n");
                meaning(related[sz - 3], ans);
            }
        }
        else if(fl1)
        {
            if (related[sz - 2].empty())
                ans.push_back("No Vietnamese meaning");
            else
            {
                ans.push_back("VIETNAMESE MEANING\n");
                meaning(related[sz - 2], ans);
            }
        }
        else
        {
            if (related[sz - 3].empty())
                ans.push_back("No English meaning");
            else
            {
                ans.push_back("ENGLISH MEANING\n");
                meaning(related[sz - 3], ans);
            }
        }
	}
	else
	{
        if (sz == 1)
        {
            ans.push_back("Something is wrong! We cannot find this word or any related words");
            ans.push_back("If you know that this word exists, please press ");
        }
		else
		{
            ans.push_back("Did you mean one of these words: ");
			for (int i = 1; i < min(sz, 11); i++)
			{
                string str = related[i] + (i == (min(sz, 10) - 1) - 1 ? "\n" : ", ");
                ans.push_back(str);
			}
		}
	}
    return ans;
}

void Trie::save(string file)
{
    cout << "Save file\n";
	ofstream fout;
	saveToFile(root, fout, 0, file);
	fout.close();
}

void Trie::saveToFile(nTrie* head, ofstream& fout, int level, string file) // function supporting save function
{
	if (head->end)
	{
		fout << "#\n";
		fout << head->definition[0] << "\n"
			<< head->definition[1] << "\n"
			<< head->definition[2]; // save words' data
	}
	if (level) fout << endl;
	for (int i = 0; i < MAX; i++)
	{
		if (!head->next[i])
			continue;
		if (level == 0 && i < 26)
		{
			string temp = file + char(i + 'a') + ".txt";
			cout << temp << endl;
			fout.open(temp);
		}
		fout << level;
		if (i < 26)
			fout << char(i + 'a');
		else fout << others[i % 26];
		saveToFile(head->next[i], fout, level + 1, file);
		if (level == 0)
			fout.close();
	}
}

void Trie::load(string file)
{
    cout << "Load file\n";
	ifstream fin;
	for (char x = 'a'; x <= 'z'; x++)
	{
		string temp = file + x + ".txt";
		cout << temp << endl;
		fin.open(temp);
		separate_data(root, "", -1, fin);
		fin.close();
	}
}

string Trie::separate_data(nTrie* head, string s, int level, ifstream& fin) // function supporting load function
{
	getline(fin, s);
	int i = 0;
	int curLevel = s[i] - '0';
	if (level >= 9 and '0' <= s[i + 1] and s[i + 1] <= '9')
		curLevel = curLevel * 10 + s[i + 1] - '0'; // case it is greater than 9: 10,11,12
	while (curLevel > level)
	{
		i = 0;
		int c;
		if (curLevel < 10)
		{
			if ('a' <= s[i + 1] and s[i + 1] <= 'z')
				c = s[i + 1] - 'a';
			else c = other(s[i + 1]);
			i += 2;
		}
		else
		{
			if ('a' <= s[i + 2] and s[i + 2] <= 'z')
				c = s[i + 2] - 'a';
			else c = other(s[i + 2]);
			i += 3;
		}
		head->next[c] = new nTrie();

		if (i < (int)s.length())
			if (s[i] == '#')
			{
				head->next[c]->end = true;
				getline(fin, s);
				head->next[c]->definition[0] = "" + s;
				getline(fin, s);
				head->next[c]->definition[1] = "" + s;
				getline(fin, s);
				head->next[c]->definition[2] = "" + s;

				if (fin.eof())
					return "";
			}
		s = separate_data(head->next[c], s, curLevel, fin);
		if (fin.eof())
			return "";

		int i = 0;
		curLevel = s[i] - '0';
		if (level >= 9 and '0' <= s[i + 1] and s[i + 1] <= '9')
			curLevel = curLevel * 10 + s[i + 1] - '0'; // case it is greater than 9: 10,11,12
	}
	return s;
}

void meaning(string s, vector<string> &ans)
{
	if (s.empty()) return;
	string sub = "";
	sub.push_back(char(92));
	sub.push_back('n');
	vector<int> index = KMP_search(s, sub, kmp_preprocess(sub));
	int sz = index.size();

	int k = 0;
	string tmp;
	tmp = string(s.begin(), s.begin() + index[0]);
    ans.push_back(tmp);

	if (sz == 1) return;

	for (int i = 1; i < sz; i++)
	{
		tmp = string(s.begin() + index[i - 1] + 2, s.begin() + index[i]);
		if (!tmp.empty())
            ans.push_back(tmp);
	}

	tmp = string(s.begin() + index[sz - 1] + 2, s.end());
    ans.push_back(tmp);
}

void continue_to_search(nTrie* root, vector<string>& related, string res)
{
	for (int i = 0; i < MAX; i++)
		if (root->next[i])
		{
			if (i < 26)
				res.push_back(i + 'a');
			else res.push_back(others[i % 26]);

			if (root->next[i]->end) related.push_back(res);
			continue_to_search(root->next[i], related, res);
			res.pop_back();
		}
	return;
}

bool Trie::check_and_add(std::string s, std::string meaning, std::string phonetic, std::string type)
{
    int n = s.length();
    nTrie* tmp = root;
    for (int i = 0; i < n; i++)
    {
        int c;
        if (('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z'))
            c = tolower(s[i]) - 'a';
        else c = other(s[i]);
        if (!tmp->next[c])
            tmp->next[c] = new nTrie();
        tmp = tmp->next[c];
    }
    if(tmp->end) return false;
    tmp->end = true;

    int k = -1;
    if (type == "English")
        k = 0;
    else
        k = 1;

    string sub = "";
    sub.push_back(char(92)); // '\n'
    sub.push_back('n');
    tmp->definition[k] += meaning;
    tmp->definition[2] += phonetic + sub;
    return true;
}
