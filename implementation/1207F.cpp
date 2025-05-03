/*
@notice: interview prep
@author: aaron
@source: https://codeforces.com/problemset/problem/1207/F
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
#define st first
#define nd second
#define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;

/*
i === y (mod x)
-> cal a[x] + a[x + y] + a[x + 2y] + ....

x=1 -> n groups
x=2 -> n/2 groups
x=3 -> n/3 groups

-> total ~nlogn groups

increase a[x] by y

just solve if there is no update query
chia can dcm

n = sqrt(500000)

if x > n
    -> just about n elements -> can iterate through. -> O(N)

if x < n
    -> T[i][j] stores sums of elements which have remainder i mod j (700 * 700).
    -> O(1)


update query
Just update every T[i][j] that element is in.
*/

const int MAXN = 5e5 + 10;
const int SQRT = 710;
int q;
int T[SQRT + 10][SQRT + 10];
int a[MAXN];


void PROGRAM(int _){
    cin >> q;

    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            a[x] += y;
            for (int i = 1; i <= SQRT; i++) {
                int pt = x % i;
                T[pt][i] += y;
            }
        }
        else {
            if (x > SQRT) {
                int ans = 0;
                for (int i = y; i <= 500000; i += x) {
                    ans += a[i];
                }
                cout << ans << endl;
            } else {
                cout << T[y][x] << endl;
            }
        }
    }
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