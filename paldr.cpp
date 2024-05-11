#include <iostream>
#include <vector>
#include <cstring>

#define MAX 10000001
using namespace std;

vector<int> palindrome_radius(char *x, bool odd = false)
{
    int n = strlen(x), i = 1, j = 0, k;
    vector<int> r(n, 0);
    while (i < n)
    {
        while (i + j + odd <= n && i - j > 0 && x[i - j - 1] == x[i + j + odd])
            ++j;
        r[i] = j;
        k = 1;
        while (r[i - k] != j - k && k <= j)
            r[i + k] = r[i - k] < j - k++;
        j = max(0, j - k);
        i += k;
    }
    return r;
}

int main()
{
    int t;
    cin >> t;
    char s[MAX];
    while (t--)
    {
        cin >> s;
        vector<int> r = palindrome_radius(s);
        int N = strlen(s), i = 0, prev_r = 0, prev_r_id = 0;
        bool valid = true;
        while (i < N)
        {
            if (r[i] != 0)
            {
                if (r[i] + prev_r < i - prev_r_id)
                {
                    valid = false;
                    break;
                }
                prev_r = r[i];
                prev_r_id = i;
            }
            i++;
        }
        cout << (!valid || prev_r_id == 0 ? "NO\n" : "YES\n");
    }
}