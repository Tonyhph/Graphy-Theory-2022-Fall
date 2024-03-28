#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    queue<int> infectDevice;
    vector<int> adj[n];
    vector<int> res;
    int visited[1000000] = {0};
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
    }
    while (k--)
    {
        int x;
        cin >> x;
        infectDevice.push(x - 1);
    }
    for (int i = 0; i < t; ++i)
    {
        if (res.size() == n)
            break;
        int max = res.size();
        for (int j = infectDevice.size(); j; --j)
        {
            if (!visited[infectDevice.front()])
            {
                res.push_back(infectDevice.front());
                for (auto k : adj[infectDevice.front()])
                    infectDevice.push(k);
                visited[infectDevice.front()] = 1;
            }
            infectDevice.pop();
        }
        if (res.size() == max)
            break;
    }
    cout << res.size() << '\n';
    return 0;
}
