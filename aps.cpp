#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define MAX 10000000

using namespace std;

typedef unsigned long long int ULL;

vector<ULL> smallestPrimeFactor;

void sieve(int n)
{
    smallestPrimeFactor.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        smallestPrimeFactor[i] = i;

    for (int i = 2; i * i <= n; ++i)
    {
        if (smallestPrimeFactor[i] == i)
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (smallestPrimeFactor[j] == j)
                {
                    smallestPrimeFactor[j] = i;
                }
            }
        }
    }
}

ULL series[MAX] = {0};
int positions_computed = 2;

void APS(int n)
{
    for (int i = positions_computed; i <= n; ++i)
    {
        series[i] = series[i - 1] + smallestPrimeFactor[i];
    }
    positions_computed = n;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(MAX);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        APS(n);
        cout << series[n] << "\n";
        }
}