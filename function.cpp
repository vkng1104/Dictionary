#include "function.h"

using namespace std;
using namespace std::chrono_literals;
namespace fs = std::filesystem;

vector<string> search(int x, string s, bool fl1, bool fl2)
{
    string file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/lastSearched.txt";
    fstream fout;
    fout.open(file, ios::app);
    fout << s << endl;
    fout.close();

//    file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/history.txt";
//    fs::file_time_type ftime = fs::last_write_time(file);
//    ftime.


    if (x == 2) // search for a definition
	{
		ifstream fin;
        vector<string> ans;
		vector<pair<int, pair<string, bool>>> vec; // used to save compatible words
		bool fl;

		for (char u = 'a';u <= 'z'; u++)
		{
			string temp = config::savedFolder + u + ".txt";
			fin.open(temp);
			
			/*
				int: degree of compatibleness
				string: that word
				bool: language --- 0: Eng and 1: Viet
			*/
			vector<string> def;
			stringstream ss(s);
			string word;
			while (ss >> word)
			{
				string temp = " " + lower(word) + " ";
				def.push_back(temp);
			}

			fl = false;
			process_a_definition(config::tries.root, "", -1, fin, def, fl, vec);
			if (fl)
			{
				int sz = (int)vec.size();
				pair<int, pair<string, bool>> u = vec[sz - 1];
                string str = "The most compatible word we can find is: " + u.second.first;
                ans.push_back(str);
                break;
			}

			fin.close();
		}

		if (!fl)
		{
			sort(vec.begin(), vec.end());
			int sz = (int)vec.size();
			pair<int, pair<string, bool>> u = vec[sz - 1];
            string str = "The most compatible word we can find is: " + u.second.first;
            ans.push_back(str);
		}

        return ans;
	}

    else if (x == 3) // slang & emotional
    {
        return searchWord(config::root, s, config::active);
    }


    // search for a keyword
    return config::tries.search(s, fl1, fl2);
}

bool isWord(string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(('A' <= s[i] and s[i] <= 'Z') or ('a' <= s[i] and s[i] <= 'z')) continue;
        else
        {
            bool flag = false;
            for(int j = 0; j < others.length(); j++)
                if(s[i] == others[j])
                {
                    flag = true;
                    break;
                }
            if(!flag) return false;
        }
    }
    return true;
}

string process_a_definition(nTrie* head, string res, int level, ifstream& fin, 
							vector<string> def, bool& flag, vector<pair<int, pair<string, bool>>>& vec)
{
	string s;
	getline(fin, s);
	int i = 0;
	int curLevel = s[i] - '0';
	if (level >= 9 and '0' <= s[i + 1] and s[i + 1] <= '9')
		curLevel = curLevel * 10 + s[i + 1] - '0'; // case it is greater than 9: 10,11,12
	while (curLevel > level)
	{
		i = 0;
		int c;
		char cur;
		if (curLevel < 10)
		{
			if ('a' <= s[i + 1] and s[i + 1] <= 'z')
				c = s[i + 1] - 'a';
			else c = other(s[i + 1]);
			cur = s[i + 1];
			i += 2;
		}
		else
		{
			if ('a' <= s[i + 2] and s[i + 2] <= 'z')
				c = s[i + 2] - 'a';
			else c = other(s[i + 2]);
			cur = s[i + 2];
			i += 3;
		}

		if (i < (int)s.length())
			if (s[i] == '#')
			{
				// cout << res + cur << endl;
				getline(fin, s);
				int deg = MAXcompatible(s, def);
				if (deg == (int)def.size())
				{
					flag = true;
					vec.push_back({ deg, {res + cur, 0} });
					return "";
				}
				else if (deg)
					vec.push_back({ deg, {res + cur, 0} });
				
				getline(fin, s);
				deg = MAXcompatible(s, def);
				if (deg == (int)def.size())
				{
					flag = true;
					vec.push_back({ deg, {res + cur, 1} });
					return "";
				}
				else if (deg)
					vec.push_back({ deg, {res + cur, 1} });

				if (fin.eof())
					return "";
				getline(fin, s);
			}
		s = process_a_definition(head->next[c], res + cur, curLevel, 
								fin, def, flag, vec);
		if (fin.eof())
			return "";

		int i = 0;
		curLevel = s[i] - '0';
		if (level >= 9 and '0' <= s[i + 1] and s[i + 1] <= '9')
			curLevel = curLevel * 10 + s[i + 1] - '0'; // case it is greater than 9: 10,11,12
	}
	return s;
}

int MAXcompatible(string s, vector<string> def)
{
	if (s.empty()) return 0;
	string sub = "";
	sub.push_back(char(92));
	sub.push_back('n');
	vector<int> index = KMP_search(s, sub, kmp_preprocess(sub));
	int sz = index.size();

	int MAX = 0;
	string tmp;
	tmp = " " + lower(string(s.begin(), s.begin() + index[0])) + " ";
	MAX = max(MAX, compatible(tmp, def));
	

	if (sz == 1) return MAX;

	for (int i = 1; i < sz; i++)
	{
		tmp = " " + lower(string(s.begin() + index[i - 1] + 2, s.begin() + index[i])) + " ";
		if (!tmp.empty())
			MAX = max(MAX, compatible(tmp, def));
	}

	tmp = " " + lower(string(s.begin() + index[sz - 1] + 2, s.end())) + " ";
	MAX = max(MAX, compatible(tmp, def));

	return MAX;
}

int compatible(string s, vector<string> def)
{
	int n = (int)def.size();
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		vector<int>idx = KMP_search(s, def[i], kmp_preprocess(def[i]));
		if ((int)idx.size()) ans++;
	}
	return ans;
}

vector<pair<string, vector<string>>> create_quiz(bool fl1, bool fl2) // fl1: 0 for word, 1 for definition ---- fl2: 0 for Eng, 1 for Viet
{
    vector<pair<string, vector<string>>> words;
    int sz = 4;
    while((int)words.size() < 4)
    {
        pair<string, vector<string>> word = randomWord();

        if(word.second.empty()) continue;

        vector<string> tmp[2];
        tmp[0] = extract_meaning(word.second[0]);
        if(tmp[0].size() < 2) continue;

        tmp[1] = extract_meaning(word.second[1]);
        if(tmp[1].size() < 2) continue;

        string phonetic = word.second[2];
        word.second.clear();
        word.second.push_back(tmp[0][1]); // english
        word.second.push_back(tmp[1][1]); // viet
        word.second.push_back(phonetic);

        bool flag = true;
        for(int i = 0; i < (int)words.size(); i++)
            if (word.first == words[i].first)
            {
                flag = false;
                break;
            }
        if(flag) words.push_back(word);
    }

    return words;
}

int random()
{
    // current date/time based on current system
    time_t now = time(0);
    // convert now to string form
    char* dt = ctime(&now);

    int ans = 0;
    int i = 0;
    while(dt[i] != '\0')
    {
        if('0' <= dt[i] and dt[i] <= '9') ans += dt[i] - '0';
        i++;
    }
    return ans;

}
pair<string, vector<string>> randomWord()
{
    int x = -1;
    nTrie* cur = config::tries.root;
    string word = "";
    vector<string> defs;

    while(1)
    {
        int x = rand() + random() + 88;
        int res = x;
        while(!cur->next[x % 26] && x < res + 26) x++;

        if(x - res == 26) break;

        int pos = x % 26;
        if(cur->next[pos])
        {
            word.push_back(pos + 'a');
            bool flag = false; // exists any NEXT word or not
            for (int i = 0; i < 26; i++)
                if (cur->next[pos]->next[i])
                {
                    flag = true;
                    break;
                }
            if(cur->next[pos]->end && (int)word.length() >= 2)
            {
                int tmp = rand() % 2; // whether to stop (1) or continue (0)
                if(tmp == 1 || !flag)
                {
                    defs.push_back(cur->next[pos]->definition[0]);
                    defs.push_back(cur->next[pos]->definition[1]);
                    defs.push_back(cur->next[pos]->definition[2]);
                    break;
                }
            }
            cur = cur->next[pos];
        }
    }
    return {word, defs};
}

vector<string> extract_meaning(string s)
{
    vector<string> alls;
    if (s.empty()) return alls;

    string sub = "";
    sub.push_back(char(92));
    sub.push_back('n');
    vector<int> index = KMP_search(s, sub, kmp_preprocess(sub));
    int sz = index.size();

    int k = 0;
    string tmp;
    tmp = string(s.begin(), s.begin() + index[0]);
    if(!tmp.empty())
        alls.push_back(tmp);

    if (sz == 1) return alls;

    for (int i = 1; i < sz; i++)
    {
        tmp = string(s.begin() + index[i - 1] + 2, s.begin() + index[i]);
        if (!tmp.empty())
            alls.push_back(tmp);
    }

    tmp = string(s.begin() + index[sz - 1] + 2, s.end());
    if(!tmp.empty())
        alls.push_back(tmp);

    return alls;
}
