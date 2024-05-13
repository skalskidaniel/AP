#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Pixel
{
    int x;
    int y;
};

int distance(Pixel p1, Pixel p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int grid[n][m];
        vector<Pixel> white_pixels;
        string line; // 1 means white - 0 means black
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int num;
                cin >> num;
                grid[n][m] = num;
                if (num == 1)
                {
                    Pixel p;
                    p.x = i;
                    p.y = j;
                    white_pixels.push_back(p);
                }

            }
        }
    }
}
