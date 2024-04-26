#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void change(int n, int index, int val, vector<vector<int> > &tab)
{
    tab[n + index][0] = val;
    int father = (n + index) / 2;
    do {
        tab[father][0] = max(tab[2 * father][0], tab[2 * father + 1][0]);
    } while (father /= 2);
}

int read(int from, int to, int nodeId, vector<vector<int> > &tab)
{
    int ans = 0;
    vector<int> current = tab[nodeId];
    if (from == current[1] && to == current[2])
    {
        ans = current[0];
    }
    else if (to <= (current[1] + current[2]) / 2)
    {
        ans = max(ans, read(from, to, 2 * nodeId, tab));
    }
    else if (from > (current[1] + current[2]) / 2)
    {
        ans = max(ans, read(from, to, 2 * nodeId + 1, tab));
    } else
    {
        ans = max(read(from, (current[1] + current[2]) / 2, 2 * nodeId, tab), read((current[1] + current[2]) / 2 + 1, to, 2 * nodeId + 1, tab));
    }
    return ans;
}

int main()
{
    // input
    std::ios_base::sync_with_stdio(false);
    int numberOfItems, requests;
    cin >> numberOfItems >> requests;

    // creating table
    // table[x][0] -> max value, table[x][1] -> from, table [x][2] -> to
    int fixedNumberOfItems = 2;
    while (fixedNumberOfItems < numberOfItems)
    {
        fixedNumberOfItems *= 2;
    }
    vector<vector<int> > table(2 * fixedNumberOfItems, vector<int>(3, 0));
    for (int idx = fixedNumberOfItems, start = 0; idx < 2 * fixedNumberOfItems; ++idx, ++start)
    {
        table[idx][1] = start;
        table[idx][2] = start;
    }
    for (int idx = fixedNumberOfItems - 1; idx > 0; --idx)
    {
        table[idx][1] = table[2 * idx][1];
        table[idx][2] = table[2 * idx + 1][2];
    }
    
    // inputing requests
    while (requests--)
    {
        int q, a, b;
        cin >> q >> a >> b;
        if (q == 1)
        {
            change(fixedNumberOfItems, a, b, table);
        } else 
        {
            cout << read(a, b, 1, table) << endl;
        }
    }
}