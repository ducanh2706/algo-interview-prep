/*
Tag: Mo Algorithm, Sqrt Decomposition, Implementation, Combinatorics
*/
#include <bits/stdc++.h>
#define ll long long
#define ii pair<int, int>
#define st first
#define nd second
#define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;
const int MAXN = 25e4 + 5;
const int SQRT_MAXN = 505;
const int MOD = 998244353;

int n, q, a[MAXN];
int fac[MAXN];
int ifac[MAXN];
int inv[MAXN];
int block_size;

struct Query {
    int l, r, x, id;

    bool operator<(const Query &other) {
        if (l / block_size != other.l / block_size) {
            return l / block_size < other.l / block_size;
        }
        return r < other.r;
    }
};

struct RangeHelper {
    int cnt[MAXN];
    int rev_fac[MAXN];
    int block_cnt[SQRT_MAXN * 2];
    int block_rev_fac[SQRT_MAXN * 2];

    void init() {
        for (int i = 0; i < SQRT_MAXN * 2; i++) {
            block_rev_fac[i] = 1;
        }
        for (int i = 0; i < MAXN; i++) {
            rev_fac[i] = 1;
        }
    }

    void increase(int x) {
        int in_block = x / SQRT_MAXN;
        assert(in_block < SQRT_MAXN);
        assert(x < MAXN);
        block_cnt[in_block]++;
        cnt[x]++;
        block_rev_fac[in_block] = (ll)block_rev_fac[in_block] * cnt[x] % MOD;
        rev_fac[x] = (ll)rev_fac[x] * cnt[x] % MOD;
    }

    void decrease(int x) {
        int in_block = x / SQRT_MAXN;
        assert(in_block < SQRT_MAXN);
        assert(x < MAXN);
        block_cnt[in_block]--;
        block_rev_fac[in_block] = (ll)block_rev_fac[in_block] * inv[cnt[x]] % MOD;
        rev_fac[x] = (ll)rev_fac[x] * inv[cnt[x]] % MOD;
        cnt[x]--;
    }

    int fac_query(int x) {
        int in_block = x / SQRT_MAXN;
        assert(in_block < SQRT_MAXN);
        assert(x < MAXN);
        int ans = 1;
        for (int i = 0; i < in_block; i++) {
            ans = (ll)ans * block_rev_fac[i] % MOD;
        }

        for (int i = SQRT_MAXN * in_block; i <= x; i++) {
            ans = (ll)ans * rev_fac[i] % MOD;
        }
        return ans;
    }

    int cnt_query(int x) {
        int ans = 0;
        int in_block = x / SQRT_MAXN;
        assert(in_block < SQRT_MAXN);
        assert(x < MAXN);
        for (int i = 0; i < in_block; i++) {
            ans += block_cnt[i];
        }

        for (int i = SQRT_MAXN * in_block; i <= x; i++) {
            ans += cnt[i];
        }

        return ans;
    }
};

Query queries[MAXN];

int binpow(int x, int y) {
    int ans = 1;

    while (y > 0) {
        if (y & 1) {
            ans = ((ll)ans * x) % MOD;
        }
        x = (ll)x * x % MOD;
        y >>= 1;
    }

    return ans;
}

void prep() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (ll)fac[i - 1] * i % MOD;
    }

    ifac[MAXN - 1] = binpow(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i >= 1; i--) {
        ifac[i - 1] = (ll)ifac[i] * i % MOD;
    }

    for (int i = 1; i < MAXN; i++) {
        inv[i] = binpow(i, MOD - 2);
    }
}

int res[MAXN];

void PROGRAM(int _){
    cin >> n >> q;

    block_size = sqrt(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= q; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].x;
        queries[i].id = i;
    }

    sort(queries + 1, queries + q + 1);

    RangeHelper helper;
    helper.init();

    int curL = 1, curR = 0;
    for (int i = 1; i <= q; i++) {
        int l = queries[i].l, r = queries[i].r, x = queries[i].x, id = queries[i].id;

        while (curL > l) {
            --curL;
            helper.increase(a[curL]);
        }

        while (curR < r) {
            ++curR;
            helper.increase(a[curR]);
        }

        while (curL < l) {
            helper.decrease(a[curL]);
            ++curL;
        }

        while (curR > r) {
            helper.decrease(a[curR]);
            --curR;
        }

        res[id] = (ll)fac[helper.cnt_query(x - 1)] * binpow(helper.fac_query(x - 1), MOD - 2) % MOD;
    }

    for (int i = 1; i <= q; i++) {
        cout << res[i] << endl;
    }
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