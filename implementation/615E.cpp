/*
@notice: interview prep
@author: aaron
@source: https://codeforces.com/contest/615/problem/E
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

int n;

/*
Every layer starts at (x, 2) and ends at (y, 0)

For example: layer 1 starts at (1, 2) and ends at (2, 0)
             layer 2 starts at (3, 2) and ends at (4, 0)

        ->   layer i starts at (i * 2 - 1, 2) and ends at (i * 2, 0)

Each layer has 6 moves: up left (-1, 2), left (-2, 0), down left (-1, -2), down right (1, -2), right (2, 0), up right (1, 2), each cross i point (in i-th layer)
*/

// calculate total points from layer 0 -> layer x

const int dx[] = {-1, -2, -1, 1, 2, 1};
const int dy[] = {2, 0, -2, -2, 0, 2};

int cal(int x) {
    // 1 + 6 + 6 * 2 + 6 * 3....
    return 1 + 6 * ((x * (x + 1) / 2));
}

int findLayer(int n) {
    ++n;
    int l = 1, r = 1e9;
    int ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cal(mid) >= n) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}
void PROGRAM(int _){
    cin >> n;
    if (n == 0) {
        cout << 0 << " " << 0 << endl;
        return;
    }

    // Outer line
    int layer = findLayer(n);
    int layerTh = n - cal(layer - 1); // 0 -> 6 * layer - 1

    int whatMove = layerTh / layer;

    // cout << layer << " " << layerTh << " " << whatMove << endl;

    int startX = layer * 2 - 1;
    int startY = 2;

    int hasMoved = 0;
    for (int t = 0; t <= whatMove; t++) {
        if (t == whatMove) {
            int rem = layerTh - hasMoved;
            startX += dx[t] * rem;
            startY += dy[t] * rem;
        } else {
            int isT0 = t == 0;
            startX += dx[t] * (layer - isT0);
            startY += dy[t] * (layer - isT0);
            hasMoved += layer - isT0;
        }
    }

    cout << startX << " " << startY << endl;







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