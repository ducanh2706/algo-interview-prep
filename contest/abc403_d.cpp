/*
Tag: DP
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
const int MAX_VAL = 1e6;
int n, d;
int a[MAX_VAL * 2];

int dp[MAX_VAL * 2][2];

void PROGRAM(int _){
    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }

    
    int ans = 0;
    if (d == 0) { 
        for (int i = 0; i <= MAX_VAL; i++) {
            ans += (a[i] > 0);
        }
        cout << n - ans << endl;
        return;
    }
    
    for (int i = 0; i <= d - 1; i++) {
        int lst = i;
        dp[i][0] = 0;
        dp[i][1] = a[i];
        for (int j = i + d; j <= MAX_VAL; j += d) {
            dp[j][0] = max(dp[j - d][0], dp[j - d][1]);
            dp[j][1] = dp[j - d][0] + a[j];
            lst = j;
        }

        ans += max(dp[lst][0], dp[lst][1]);
    }
    cout << n - ans;
   
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