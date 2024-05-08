#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

vector<int> get_lps(string s)
{
    vector<int> LPS(s.size(), 0);
    int i = 1, j = 0;
    while (i < s.size())
    {
        if (s[i] == s[j])
        {
            ++j;
            LPS[i] = j;
            ++i;
        } else if (j > 0)
        {
            j = LPS[j - 1];
        } else
        {
            LPS[i] = 0;
            ++i;
        }
    }
    return LPS;
}
void kmp(string pattern, string text)
{
    if (pattern.size() > text.size())
    {
        return;
    }
    else
    {
        if (pattern.size() == text.size())
        {
            if (pattern == text)
                cout << 0 << endl;
            else
                return;
        }
        if (pattern == "")
        {
            cout << 0 << endl;
            return;
        }
        vector<int> lps = get_lps(text);
        int i = 0, j = 0;
        while (i < text.size())
        {
            if (text[i] == pattern[j])
            {
                ++i;
                ++j;
            }
            if (j == pattern.size())
            {
                cout << i - j << endl;
                j = lps[j - 1];
            }
            else if (i < text.size() && text[i] != pattern[j])
            {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    ++i;
                }
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        string pattern, text;
        cin >> n >> pattern >> text;
        kmp(pattern, text);
    }

}