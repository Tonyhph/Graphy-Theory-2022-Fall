#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int> > Graph(n);
    vector<int> deg(n), cnt(n), vis(n,2);
    int a, b;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> a >> b;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
        ++deg[a];
        ++deg[b];
    }
    queue<int> q;
    for(int i = 0;i < n;++i){
        if(deg[i] == 1){
            q.push(i);
            cnt[i] = 1;
            vis[i] = 1;
        }
        else if(deg[i] == 3)
            vis[i] = 3;
    }
    int cur;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        for(int i:Graph[cur]){
            if(vis[i] != 1){
                --deg[i];
                --deg[cur];
                if(vis[i] == 2 && deg[i] == 1){
                    vis[i] = 1;
                    cnt[i] = cnt[cur] + 1;
                    q.push(i);
                }
            }
        }
    }
    vector<int> pos;
    for(int i = 1; i < n; ++i){
        if(deg[i] <= 1 && vis[i] ==3)
            pos.push_back(i);
    }
    
    int m;
    cin>>m;
    vector<int> key(m);
    for(int i = 0; i < m;++i)
        cin>>key[i];
    if(pos.size() == 1){
        if(m != 1){
            cout<<"NO\n";
            return 0;
        }
        unordered_set<int> st;
        for(int j : Graph[pos[0]]){
            if(vis[j] == 1){
                st.insert(cnt[j]);
            }
        }
        if(st.count(key[0])){
            cout<<"YES\n";
            return 0;
        }
    }
    else{
        int pre;
        for(int i = 0; i < 2; ++i){
            pre = -1;
            vector<int> tmp;
            q.push(pos[i]);
            while(!q.empty()){
                int cur = q.front();
                q.pop();
                for(int j : Graph[cur]){
                    if(vis[j] == 1)
                        tmp.push_back(cnt[j]);
                    if(j == pre || vis[j] == 1)
                        continue;
                    q.push(j);
                }
                pre = cur;
            }
            bool  flag = false;
            if((int)tmp.size() == m + 2){
                if(tmp[0] == key[0] || tmp[1] == key[0]){
                    if(tmp[m + 1] == key[m - 1] || tmp[m] == key[m-1]){
                        flag = true;
                        for(int i = 1; i < m - 1; ++i){
                            if(key[i] != tmp[i + 1]){
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }
            if(flag){
                cout<<"YES\n";
                return 0;
            }
        
        }

    }
    cout<<"NO\n";

    return 0;
}