/*
Tag: Combinatorics
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
const int MAXN = 4e6 + 5;
const int MOD = 998244353;

int fac[MAXN];
int ifac[MAXN];


int binpow(int x, int y) {
    int ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = (ans * x) % MOD;
        }
        y >>= 1;
        x = (x * x) % MOD;
    }
    return ans;
}

int C(int n, int k) {
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void prep() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    ifac[MAXN - 1] = binpow(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i >= 1; i--) {
        ifac[i - 1] = (ifac[i] * i) % MOD;
    }

}


void PROGRAM(int _){
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int n = a + b + c + d;
    int ans = 0;
    // choose first position of grape
    for (int i = a + b + 1; i <= n; i++) { 
        // choose d - 1 position out of n - i position left
        if (n - i < d - 1) {
            break;
        }

        int temp = C(n - i, d - 1);

        // fill "unfilled" other position from i with banana
        int left_banana = c - ((n - i + 1) - d);
        if (left_banana < 0) {
            continue;
        }

        // fill [1..i - 1] with apple + banana
        temp = (temp * C(i - 1, a + left_banana)) % MOD;
        ans = (ans + temp) % MOD;
    }
    cout << ans << endl;
    
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    prep();

    int test = 1;

    for (int _ = 1; _ <= test; _++){
        PROGRAM(_);
    }

    return 0;
}