#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string addBigNumbers(const string &a, const string &b)
{
    string result = "";
    int carry = 0;
    int a_len = a.length();
    int b_len = b.length();
    int max_len = max(a_len, b_len);

    for (int i = 0; i < max_len; ++i)
    {
        int digitA = (i < a_len) ? a[a_len - 1 - i] - '0' : 0;
        int digitB = (i < b_len) ? b[b_len - 1 - i] - '0' : 0;
        int sum = digitA + digitB + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    if (carry)
    {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

string multiplyByTwo(const string &num)
{
    string result = "";
    int carry = 0;
    for (int i = num.length() - 1; i >= 0; --i)
    {
        int digit = num[i] - '0';
        int prod = digit * 2 + carry;
        result.push_back((prod % 10) + '0');
        carry = prod / 10;
    }

    if (carry)
    {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

string subtractTwo(const string &num)
{
    string result = num;
    int n = result.length();

    // Subtract 2 from the last digit
    if (result[n - 1] >= '2')
    {
        result[n - 1] -= 2;
    }
    else
    {
        // Borrowing
        result[n - 1] = '8';
        int i = n - 2;
        while (i >= 0 && result[i] == '0')
        {
            result[i] = '9';
            i--;
        }
        if (i >= 0)
        {
            result[i]--;
        }
        else
        {
            result = "0";
        }
    }

    // Remove leading zeros if any
    size_t non_zero_index = result.find_first_not_of('0');
    if (non_zero_index != string::npos)
    {
        result = result.substr(non_zero_index);
    }
    else
    {
        result = "0";
    }

    return result.empty() ? "0" : result;
}

int main()
{
    vector<string> inputs;
    string line;

    // Reading input from standard input
    while (cin >> line)
    {
        inputs.push_back(line);
    }

    for (const string &N : inputs)
    {
        string result;
        if (N == "1")
        {
            result = N;
        }
        else
        {
            result = multiplyByTwo(N);
            result = subtractTwo(result);
        }
        cout << result << endl;
    }

    return 0;
}
