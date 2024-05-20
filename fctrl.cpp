#include <iostream>
using namespace std;

unsigned int countTrailingZeros(unsigned int n)
{
    int count = 0;
    for (long long i = 5; n / i >= 1; i *= 5)
    {
        count += n / i;
    }
    return count;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        unsigned int N;
        cin >> N;
        cout << countTrailingZeros(N) << '\n';
    }

    return 0;
}
