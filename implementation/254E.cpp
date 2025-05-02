/*
@notice: interview prep
@author: aaron
@source: https://codeforces.com/problemset/problem/254/E
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
#define st first
#define nd second
// #define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;

/*
- Find maximum reputation can reach first
f[i][j]: maximum reputation can reach til day i, still has j kilograms of food left.
keep a list of friends that need eating at day i, sorted by f ascending.

-> for i, j, t: 0->x (number of friends can eat at day i) (400^3)
        x: prev day leftovers.
    -> 400 ^ 4
    actually with j, x can find maximum number of friends can be fed (use 2 pointer)
    with j - x -> can feed (a[i] - j) + x - v for friends.
    -> 400^3
*/

const int MAXN = 405;

int dp[MAXN][MAXN];
pair<int, int> trace[MAXN][MAXN];
int n, v;
int a[MAXN];
vector<pair<int, int>> g[MAXN];
vector<int> res[MAXN];
int m;

void PROGRAM(int _){
    cin >> n >> v;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r, f;
        cin >> l >> r >> f;
        for (int j = l; j <= r; j++) {
            g[j].push_back({f, i});
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(all(g[i]));
    }

    dp[0][0] = 0;

    // initialize
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= a[i]; j++) {
            dp[i][j] = -1e9;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= a[i]; j++) {
            int total = 0;
            int pt = 0;
            for (int x = 0; x <= a[i - 1]; x++) {
                int feed = a[i] - j + x - v;
                // he can't even feed himself :cry:
                if (feed < 0) {
                    continue;
                }
                
                while (pt < g[i].size() && g[i][pt].st + total <= feed) {
                    total += g[i][pt].st;
                    pt++;
                }

                if (dp[i][j] < dp[i - 1][x] + pt) {
                    dp[i][j] = dp[i - 1][x] + pt;
                    trace[i][j] = {x, pt};
                }
            }
        }
    }

    int ans = 0;
    int j;
    for (int i = 0; i <= a[n]; i++) {
        if (dp[n][i] > ans) {
            ans = dp[n][i];
            j = i;
        }
    }

    cout << ans << endl;

    if (ans == 0) {
        for (int i = 1; i <= n; i++) cout << 0 << endl;
        return;
    }

    int temp = n;
    while (temp > 0) {
        pair<int, int> t = trace[temp][j];
        for (int id = 0; id < t.nd; id++) {
            res[temp].push_back(g[temp][id].nd);
        }
        j = t.first;
        --temp;
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i].size() << " ";
        for (auto &x : res[i]) cout << x << " ";
        cout << endl;
    }
    
}

signed main(){
    if(fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int test = 1;

    for (int _ = 1; _ <= test; _++){
        PROGRAM(_);
    }

    return 0;
}