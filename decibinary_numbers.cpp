#include <bits/stdc++.h>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

long long int dp[25][300005] = {};
long long int nm[300005] = {};

long long int same_val_nums(int d, int s)
{
    if (d == -1 && s == 0)
        return 1;
    else if (d == -1)
        return 0;
    else if (dp[d][s] == -1)
    {
        dp[d][s] = 0;
        for (int i = 0; i <= 9 && (1 << d) * i <= s; i++)
            dp[d][s] += same_val_nums(d - 1, s - ((1 << d) * i));
    }
    return dp[d][s];
}
int lowest, highest, ans;
string decibinaryNumbers(long x)
{
    string number;
    if (x == 1) number = '0';
    else
    {
        lowest = 0;
        highest = 300004;
        while (lowest <= highest)
        {
            int mid = (lowest + highest) / 2;
            if (nm[mid] >= x)
            {
                ans = mid;
                highest = mid - 1;
            }
            else
                lowest = mid + 1;
        }

        long long int g = x - nm[ans - 1];
        long long int cur = ans;
        long long int val;
        int dig;

        for (int i = -1; same_val_nums(i, cur) < g; i++)
            dig = i;
        dig++;

        while (dig >= 0)
        {
            val = 0;
            for (int i = 0; i <= 9; i++)
            {
                if ((cur - (1 << dig) * i) >= 0)
                    val += same_val_nums(dig - 1, cur - (1 << dig) * i);
                if (val >= g)
                {
                    number += to_string(i);
                    g -= val - same_val_nums(dig - 1, cur - (1 << dig) * i);
                    cur -= (1 << dig) * i;
                    break;
                }
            }
            dig--;
        }
    }
    return number;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 300005; j++)
            dp[i][j] = -1;
    for (int i = 0; i < 300005; i++)
        nm[i] = same_val_nums(24, i);
    for (int i = 1; i < 300005; i++)
        nm[i] += nm[i - 1];
    

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string x_temp;
        getline(cin, x_temp);

        long x = stol(ltrim(rtrim(x_temp)));

        string result = decibinaryNumbers(x);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}
