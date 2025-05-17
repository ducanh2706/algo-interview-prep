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

const int MAXN = 3e5 + 5;

int n, a[MAXN];
int lst[MAXN];

void PROGRAM(int _){
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    int prev_dp = 0;

    for (int i = 1; i <= n; i++) {
        int pos_x = lst[a[i]];
        int pos_x__1 = lst[a[i] - 1];
        int pos_x_1 = lst[a[i] + 1];
        int mx = max(pos_x__1, pos_x_1);
        int mn = min(pos_x__1, pos_x_1);
        int dp;

        if (pos_x < min(pos_x__1, pos_x_1)) {
            dp = 1 + prev_dp + (i - mx - 1) - (mn - pos_x);
        }
        else {
            mx = max(mx, pos_x);
            dp = 1 + prev_dp + (i - mx - 1);
        }

        if (i == 1) ans += 1, prev_dp = 1;
        else ans += dp, prev_dp = dp;
        lst[a[i]] = i;
    }

    cout << ans << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int test = 1;
    // cin >> test;

    for (int _ = 1; _ <= test; _++){
        PROGRAM(_);
    }

    return 0;
}