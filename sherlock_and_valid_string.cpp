#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s)
{
    int occurrencies[26] = {0};
    for (auto chr : s)
    {
        ++occurrencies[chr - 'a'];
    }

    int val = 0, hmdif = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (occurrencies[i] != 0)
        {
            if (!val) // set base value to check differences
            {
                val = occurrencies[i];
            }
            if (occurrencies[i] != val)
            {
                if ((abs(occurrencies[i] - val) != 1 && occurrencies[i] != 1) || hmdif == 1)
                {
                    return "NO";
                } else
                {
                    ++hmdif;
                }
            }
        }
    }
    return "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
