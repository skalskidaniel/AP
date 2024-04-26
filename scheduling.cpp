#include <iostream>
#include <vector>
#define ULL unsigned long long

using namespace std;

int main()
{
    ULL n; 
    cin >> n;
    vector<ULL> times;
    for (ULL m = 0; m < n; ++m)
    {
        ULL task; cin >> task;
        times.push_back(task);
    }

    for (ULL id = 0; id < n; ++id)
    {
        ULL currentTaskTime = times[id];
        ULL ans = currentTaskTime;
        // tasks before
        for (ULL i = 0; i < id; ++i)
        {
            ULL timeToAdd = (times[i] < currentTaskTime) ? times[i] : currentTaskTime;
            ans += timeToAdd;
        }
        // tasks after
        for (ULL i = id + 1; i < n; ++i)
        {
            ULL timeToAdd = (times[i] < currentTaskTime) ? times[i] : currentTaskTime - 1;
            ans += timeToAdd;
        }
        
        cout << ans << "\n";
    }
}