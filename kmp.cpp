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

int main() {
    int t;
    cin >> t;
    while(t--)
    {
        
    }

}