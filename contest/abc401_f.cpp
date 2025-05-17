/*
Tag: 
*/
#include <bits/stdc++.h>
#define int long long
#define ii pair<int, int>
#define st first
#define nd second
#define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;

const int MAXN = 2e5 + 5;

struct Graph {
    int n;
    vector<vector<int>> g;
    vector<int> dist;
    vector<vector<int>> d;

    Graph(int _n) {
        n = _n;
        g = vector<vector<int>>(n + 1);
        dist = vector<int>(n + 1);
        d = vector<vector<int>>(2, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            dist[i] = d[0][i] = d[1][i] = 0;
        }
    }
    
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int par, vector<int> &d, int &max_node) {
        if (d[u] > d[max_node]) {
            max_node = u;
        }

        for (auto &v : g[u]) {
            if (v == par) continue;
            d[v] = d[u] + 1;
            dfs(v, u, d, max_node);
        }
    }

    int find_diameter() {
        int endpoint0 = 0, endpoint1 = 0;
        int dumb = 0;
        dfs(1, 0, d[0], endpoint0);
        dfs(endpoint0, 0, d[1], endpoint1);
        for (auto &v : d[0]) v = 0;
        dfs(endpoint1, 0, d[0], dumb);
        

        for (int i = 1; i <= n; i++) {
            dist[i] = max(d[0][i], d[1][i]);
        }

        return d[1][endpoint1];
    }
};

int n1, n2;
int pref[MAXN];



void PROGRAM(int _){
    cin >> n1;
    Graph tree1(n1);
    for (int i = 1; i <= n1 - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree1.add_edge(u, v);
    }

    cin >> n2;
    Graph tree2(n2);
    for (int i = 1; i <= n2 - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree2.add_edge(u, v);
    }

    int dia1 = tree1.find_diameter();
    int dia2 = tree2.find_diameter();

    sort(tree1.dist.begin() + 1, tree1.dist.begin() + n1 + 1, greater<int>());
    sort(tree2.dist.begin() + 1, tree2.dist.begin() + n2 + 1);

    for (int i = 1; i <= n2; i++) {
        pref[i] = pref[i - 1] + tree2.dist[i];
    }

    int ans = 0;
    int l = 0;

    for (int i = 1; i <= n1; i++) {
        while (l < n2 && tree1.dist[i] + tree2.dist[l + 1] + 1 <= max(dia1, dia2)) {
            l++;
        }

        ans += max(dia1, dia2) * l + tree1.dist[i] * (n2 - l) + pref[n2] - pref[l] + (n2 - l);
    }
    cout << ans << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int test = 1;

    for (int _ = 1; _ <= test; _++){
        PROGRAM(_);
    }

    return 0;
}