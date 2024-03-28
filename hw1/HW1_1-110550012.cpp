#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m; // n verices and m edges
    cin >> n >> m;

    int GraphMatrix[n][n];
    memset(GraphMatrix, 0, sizeof(GraphMatrix));
    // m lines  ui->vi  wi :weights
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        GraphMatrix[u - 1][v - 1] = w;
    }

    // ouput matrix
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
            cout << GraphMatrix[i][j] << ' ';
        cout << GraphMatrix[i][n - 1] << '\n';
    }
    for (int i = 0; i < n; ++i)
    {
        int in = 0, out = 0;
        for (int j = 0; j < n; ++j)
        {
            if (GraphMatrix[j][i] != 0)
                ++in;
            if (GraphMatrix[i][j] != 0)
                ++out;
        }
        cout << in << ' ' << out << '\n';
    }
}