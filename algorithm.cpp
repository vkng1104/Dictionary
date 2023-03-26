#include "algorithm.h"
using namespace std;

vector<int> kmp_preprocess(string sub)
{
    int m = sub.length();
    vector<int> prefix(m, 0);

    int j = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && sub[i] != sub[j])
            j = prefix[j - 1];
        if (sub[i] == sub[j])
            j++;
        prefix[i] = j;
    }
    return prefix;
}

vector<int> KMP_search(string s, string sub, vector<int> prefix) // Knuth-Morris-Pratt algorithm
{
    int n = s.length();
    int m = sub.length();
    vector<int> found;

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && s[i] != sub[j])
            j = prefix[j - 1];
        if (s[i] == sub[j])
            j++;
        if (j == m)
        {
            found.push_back(i - m + 1);
            j = prefix[j - 1];
        }
    }
    return found;
}

string lower(string str)
{
    int n = (int)str.length();
    string ans = "";
    for (int i = 0; i < n; i++)
    {
        if ('A' <= str[i] and str[i] <= 'Z')
            ans.push_back(tolower(str[i]));
        else ans.push_back(str[i]);
    }
    return ans;
}
