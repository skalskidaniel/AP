#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define N 100000

using namespace std;

vector<int> parent(N, -1);
vector<int> neighbourhood_size(N, 1);

int find(int x)
{
    if (parent[x] == -1)
        return x;
    return parent[x] = find(parent[x]);
}

void connect_houses(int x, int y)
{
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y)
    {
        parent[root_x] = root_y;
        neighbourhood_size[root_y] += neighbourhood_size[root_x];
    }
}

int main()
{
    int people, queries;
    cin >> people >> queries;

    while (queries--)
    {
        string type;
        int p1, p2;
        cin >> type;
        if (type == "M")
        {
            cin >> p1 >> p2;
            connect_houses(p1, p2);
        }
        else if (type == "Q")
        {
            cin >> p1;
            cout << neighbourhood_size[find(p1)] << endl;
        }
    }

    return 0;
}
