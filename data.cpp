#include "data.h"
using namespace std;

std::string feature[] = { ".", " see", " prefix", " suffix", " note" };
const int numFeatures = 4;

int processMeaning(string s) // all cases with meaning: n.  v.  adj.  adv.  abbr.  adv. & prep.  prep.
{
    int ans = s.length();
    for (int i = 0; i < numFeatures; i++)
    {
        vector<int> cur = KMP_search(s, feature[i], kmp_preprocess(feature[i]));
        if (cur.empty())
            continue;
        ans = min(ans, cur[0]);
    }
    return ans;
}

void processDatabase1() // EngEngraw.txt
{
    ifstream fin("EngEngraw.txt");
    ofstream fout("processed_database/eng_eng/1.txt");
    string s;
    while (getline(fin, s))
    {
        s = "" + s;
        int n = s.length();
        if (s.empty() or n == 1)
            continue;
        int idx = processMeaning(s);
        string word(s.begin(), s.begin() + idx);
        int w = 1;
        while (!word.empty())
        {
            w = word.length() - 1;
            if (word[w] == ' ')
                break;
            word.pop_back();
        }
        if (word.empty())
        {
            int w = 0;
            while (1)
            {
                if (s[w] == ' ')
                    break;
                word.push_back(s[w++]);
            }
            idx = word.length();
        }
        else
        {
            idx = word.length();
            while (1)
            {
                w = word.length() - 1;
                if (word[w] != ' ')
                    break;
                word.pop_back();
            }
        }
        string meaning(s.begin() + idx, s.end());
        fout << word << ";" << meaning << "\n";

        // trie.add(word, meaning);
    }
    fin.close();
    fout.close();
}

void processDatabase2() // EngVietraw.txt
{
    ifstream fin("EngVietraw.txt");
    ofstream fout("processed_database/eng_viet/1.txt");
    string s;
    string t = "";
    int i = 0;
    while (getline(fin, s))
    {
        i++;
        s = "" + s;
        int n = s.length();
        if (s.empty())
            continue;
        // cout << s << endl;
        if (s[0] == '@')
        {
            if (i > 1)
                fout << endl;
            int n = s.length();
            int idx = n;
            for (int r = 1; r < n; r++)
                if (s[r] == '/')
                {
                    idx = r;
                    break;
                }
            string tmp[2];
            tmp[0] = string(s.begin() + 1, s.begin() + idx - 1);
            tmp[1] = string(s.begin() + idx, s.end());

            fout << tmp[0] << ";;;" << tmp[1] << ";;;";
            continue;
        }
        fout << s << char(92) << "n";
    }
    fin.close();
    fout.close();
}

void loadData(Trie& trie, string file, string language)
{
    ifstream fin(file);
    string s;
    if (fin.is_open()) 
    {
        while (getline(fin, s))
        {
            vector<int> index = KMP_search(s, ";;;", kmp_preprocess(";;;"));
            string tmp[3];
            tmp[0] = string(s.begin(), s.begin() + index[0]);
            if(index[0] + 1 < index[1])
                tmp[1] = string(s.begin() + index[0] + 3, s.begin() + index[1]);
            tmp[2] = string(s.begin() + index[index.size() - 1] + 3, s.end());

            trie.add(tmp[0], tmp[2], tmp[1], language);
        }
    }
    else cout << "FILES NOT FOUND!!!\n";
    fin.close();
}

void loadData2(Trie& trie, string file, string language)
{
    for (char x = 'a'; x <= 'z'; x++)
    {
        string temp = file + x + ".txt";
        ifstream fin(temp);
        string s;
        if (fin.is_open())
        {
            while (getline(fin, s))
            {
                vector<int> index = KMP_search(s, ",", kmp_preprocess(","));

                string tmp[2];
                tmp[0] = string(s.begin(), s.begin() + index[0]);
                tmp[1] = "* " + string(s.begin() + index[0] + 2, s.begin() + index[1] - 1) + char(92) + "n" + string(s.begin() + index[1] + 1, s.end());

                trie.add(tmp[0], tmp[1], "", language);
            }
        }
        else cout << "FILES NOT FOUND!!!\n";
        fin.close();
    }
}

bool isEmpty_file(string file)
{
    ifstream fin("myfile.txt");
    if(fin.is_open())
    {
        fin.seekg(0,ios::end);
        size_t size = fin.tellg();
        if( size == 0)
        return true;
    }
    return false;
}

void SEinit() // slang - emo initialization
{
    queue<string> history;
    bool open = true;
    char file_name[21];
    char a[200], def[200];
    int n, choice = 1;
    config::active = new active_point;
    config::root = new node;

    getFile("C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/slang", config::root);
    getFile("C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/emotional", config::root);
}

void initialize()
{
    if(isEmpty_file(config::savedFolder + "a.txt"))
    {
        loadData(config::tries, "C:/Users/ASUS/projects/QChi/KTLT_Lavie/CS163/processed_database/eng_viet/1.txt", "Viet");
        loadData2(config::tries, "C:/Users/ASUS/projects/QChi/KTLT_Lavie/CS163/processed_database/eng_eng/database 1/", "English");
        config::tries.save(config::savedFolder);
    }
    else
        config::tries.load(config::savedFolder);

    // slang - emo
    SEinit();

    string file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/history.txt";
    if(isEmpty_file(file))
    {
        ofstream(file).put('a');
    }
}

void resetData()
{
    Trie newTrie;
    loadData(newTrie, "C:/Users/ASUS/projects/QChi/KTLT_Lavie/CS163/processed_database/eng_viet/1.txt", "Viet");
    loadData2(newTrie, "C:/Users/ASUS/projects/QChi/KTLT_Lavie/CS163/processed_database/eng_eng/database 1/", "English");
    config::tries = newTrie;
    config::tries.save(config::savedFolder);

    // slang - emo
    SEinit();
}

