#include <bits/stdc++.h>
using namespace std;
#define LL long long
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    LL Q;
    cin >> Q;
    while (Q--)
    {
        bool Yes = true;
        LL n, m;
        cin >> n >> m;
        vector<LL> d(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> d[i];
            if (d[i] > n)
                Yes = false;
        }
        while (m--)
        {
            LL u, v;
            cin >> u >> v;
            --d[u];
            --d[v];
            if (d[u] < 0 || d[v] < 0)
                Yes = false;
        }
        sort(d.begin() + 1, d.end(), greater<LL>());
        vector<LL> sum_d(n + 1);
        for (LL i = 1; i <= n; ++i)
            sum_d[i] = sum_d[i - 1] + d[i];
        if ((sum_d[n] & 1) == 1)
            Yes = false;
        if (Yes)
        {
            LL p = n;
            for (LL k = 1; k <= n; ++k)
            {
                while (k > d[p] && k < p)
                    --p;
                while (k > p)
                    ++p;
                LL right = k * (p - k) + sum_d[n] - sum_d[p];
                if (sum_d[k] > k * (k - 1) + right)
                    Yes = false;
            }
        }
        if (Yes)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}