#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#define MAX 128*128

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

int lowest_distance(Pixel p1, vector<Pixel> white_pixels)
{
    int lowest = MAX;
    for (auto p2 : white_pixels)
    {
        int current_distance = distance(p1, p2);
        if (current_distance < lowest)
            lowest = current_distance;
    }
    return lowest;
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
        for (int i = 0; i < n; ++i)
        {
            string line; // 1 means white - 0 means black
            cin >> line;
            for (int j = 0; j < m; ++j)
            {
                int num = line[j] - '0';
                grid[i][j] = num;
                if (num == 1)
                {
                    Pixel p;
                    p.x = i;
                    p.y = j;
                    white_pixels.push_back(p);
                }

            }
        }

        // now display dist to nearest white space for each pixel
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                Pixel p;
                p.x = i;
                p.y = j;
                cout << lowest_distance(p, white_pixels) << " ";
            }
            cout << "\n";
        }
    }
}
