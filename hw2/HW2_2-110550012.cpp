#include <bits/stdc++.h>
using namespace std;
class TreeNode
{
public:
    int index;
    vector<TreeNode *> children;
    TreeNode *parent;
    int depth;
    TreeNode() {}
    TreeNode(int _index)
    {
        index = _index;
    }
};
class MinSparseTable
{
public:
    int n;
    int P;
    vector<int> log2;
    vector<vector<long> > dp;
    vector<vector<int> > it;

    MinSparseTable(vector<int> depth)
    {
        init(depth);
    }

    void init(vector<int> v)
    {
        n = v.size();
        P = (int)(log(n - 1) / log(2));
        dp.resize(P+1, vector<long>(n));
        it.resize(P+1, vector<int>(n));
        for (int i = 1; i < n; ++i)
        {
            dp[0][i] = v[i];
            it[0][i] = i;
        }
        log2.resize(n+1);
        for (int i = 2; i <= n; ++i)
        {
            log2[i] = log2[i / 2] + 1;
        }
        for (int p = 1; p <= P; ++p)
        {
            for (int i = 1; i + (1 << p) <= n; ++i)
            {
                long leftInterval = dp[p - 1][i];
                long RightInterval = dp[p - 1][i + (1 << (p - 1))];
                dp[p][i] = min(leftInterval, RightInterval);

                if (leftInterval <= RightInterval)
                    it[p][i] = it[p - 1][i];
                else
                    it[p][i] = it[p - 1][i + (1 << (p - 1))];
            }
        }
    }

    int queryIndex(int l, int r)
    {
        int p = log2[r - l + 1];
        long leftInterval = dp[p][l];
        long rightInterval = dp[p][r - (1 << p) + 1];
        if (leftInterval <= rightInterval)
            return it[p][l];
        else
            return it[p][r - (1 << p) + 1];
    }
};

int tour_index = 1;
void visit(TreeNode *node, vector<int> &depth, vector<int> &nodes, vector<int> &last)
{
    nodes[tour_index] = node->index;
    depth[tour_index] = node->depth;
    last[node->index] = tour_index;
    ++tour_index;
}
void DFS(TreeNode *node, vector<int> &depth, vector<int> &nodes, vector<int> &last)
{
    if (node == NULL)
        return;
    visit(node, depth, nodes, last);
    for (TreeNode *child : node->children)
    {
        DFS(child, depth, nodes, last);
        visit(node, depth, nodes, last);
    }
}

int findLCA(int u, int v, vector<int> &last, vector<int>&nodes, MinSparseTable *sparseTable)
{
    int l = min(last[u], last[v]);
    int r = max(last[u], last[v]);
    int i = sparseTable->queryIndex(l,r);
    return nodes[i]; //
}

int getDistance(TreeNode *LCA, TreeNode *node)
{
    return node->depth - LCA->depth;
}
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n; // a tree with n vertices and n-1 edges
    cin >> n;
    vector<TreeNode *> nodeList(n + 1);
    for (int i = 1; i <= n; ++i)
        nodeList[i] = new TreeNode(i);
    int x, y;
    nodeList[1]->depth = 0; //default depth = 0
    nodeList[1]->parent = NULL; //default
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> x >> y; // indicate the unique edge connect vetice x and y with length 1
        nodeList[x]->children.push_back(nodeList[y]);
        nodeList[y]->depth = nodeList[x]->depth + 1;
        nodeList[y]->parent = nodeList[x];
    }

    vector<int> depth(2 * n);
    vector<int> nodes(2 * n);
    vector<int> last(n + 1);

    DFS(nodeList[1], depth, nodes, last);
    MinSparseTable *sparseTable = new MinSparseTable(depth);

    int Q; // num of queries
    cin >> Q;
    int u, v;
    for (int i = 0; i < Q; ++i)
    {
        cin >> u >> v; // mean asked to find out length from u to v
        TreeNode *LCA = nodeList[findLCA(u, v, last, nodes, sparseTable)];
        int root_u_len = getDistance(LCA, nodeList[u]);
        int root_v_len = getDistance(LCA, nodeList[v]);
        cout << root_u_len + root_v_len << '\n';
    }
}