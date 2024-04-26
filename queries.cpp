#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


struct Node
{
    int sum, result, preRes, sufRes;
    Node() {}
    Node(int val)
    {
        sum = result = preRes = sufRes = val;
    }
};
int const N = 50001;
int n, m, a[N], s, e;
Node segment[N * 4];


Node merge(Node left, Node right)
{
    Node ans;
    ans.sum = left.sum + right.sum;
    ans.preRes = max(left.preRes, left.sum + right.preRes);
    ans.sufRes = max(right.sufRes, right.sum + left.sufRes);
    ans.result = max(left.result, max(right.result, left.sufRes + right.preRes));
    return ans;
}
void init(int at, int l, int r)
{
    if (l == r)
    {
        segment[at] = Node(a[l]);
        return;
    }

    int m = (l + r) / 2;
    init(at * 2, l, m);
    init(at * 2 + 1, m + 1, r);
    segment[at] = merge(segment[at * 2], segment[at * 2 + 1]);
}
Node get(int at, int l, int r)
{
    if (l > e || r < s)
        return Node(-1000000);

    if (l >= s && r <= e)
        return segment[at];

    int m = (l + r) / 2;
    return merge(get(at * 2, l, m), get(at * 2 + 1, m + 1, r));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <=n; ++i)
    {
        cin >> a[i];
    }
    init(1, 1, n);
    int m;
    cin >> m;
    while (m--)
    {
        
        cin >> s >> e;
        cout << get(1, 1, n).result << endl;
    }


}
