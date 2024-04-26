#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

typedef unsigned long long int ull;

string addBigNums(string a, string b) {
    int carry = 0;
    string result;
    
    // Make sure both strings have the same length by adding leading zeros if necessary
    int maxLength = max(a.length(), b.length());
    a = string(maxLength - a.length(), '0') + a;
    b = string(maxLength - b.length(), '0') + b;

    for (int i = maxLength - 1; i >= 0; --i) {
        int digitSum = (a[i] - '0') + (b[i] - '0') + carry;
        result = to_string(digitSum % 10) + result;
        carry = digitSum / 10;
    }

    // If there's a carry left, add it to the result
    if (carry) {
        result = to_string(carry) + result;
    }

    return result;
}

string subtractBigNums(string a, string b) {
    string result;
    int borrow = 0;
    
    // Make sure both strings have the same length by adding leading zeros if necessary
    int maxLength = max(a.length(), b.length());
    a = string(maxLength - a.length(), '0') + a;
    b = string(maxLength - b.length(), '0') + b;

    for (int i = maxLength - 1; i >= 0; --i) {
        int digitDiff = (a[i] - '0') - (b[i] - '0') - borrow;
        if (digitDiff < 0) {
            digitDiff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = to_string(digitDiff) + result;
    }

    // Remove leading zeros from result
    result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));

    return result;
}

string divideByTwo(string num) {
    string result;
    int remainder = 0;
    bool leadingZero = true;
    for (char digit : num) {
        int currentDigit = digit - '0';
        int quotient = (currentDigit + remainder * 10) / 2;
        remainder = (currentDigit + remainder * 10) % 2;
        if (quotient > 0 || !leadingZero) {
            result.push_back(quotient + '0');
            leadingZero = false;
        }
    }
    if (result.empty()) {
        result.push_back('0');
    }
    return result;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    string a, b;
    while (cin >> a >> b)
    {
        
        string n = divideByTwo(subtractBigNums(a, b));
        string k = divideByTwo(addBigNums(a, b));
        cout << k << '\n' << n << '\n';
        }
}

/*
natalia                        n = (a - b)/2

klaudia                        k = (a + b)/2

*/