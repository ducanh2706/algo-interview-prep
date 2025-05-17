/*
Tag: Dijkstra
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

int n, k;
int a[MAXN];
int b[MAXN];
int c[MAXN];

struct Node {
    int val;
    int i, j, k;


    Node(int _i, int _j, int _k) {
        i = _i;
        j = _j;
        k = _k;
        val = a[i] * b[j] + b[j] * c[k] + c[k] * a[i];
    }

    bool operator<(const Node &other) const {
        if (val != other.val) {
            return val < other.val;
        }
        if (i != other.i) {
            return i < other.i;
        }

        if (j != other.j) {
            return j < other.j;
        }
        return k < other.k;
    }
};



void PROGRAM(int _){
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    sort(a + 1, a + n + 1, greater<int>());
    sort(b + 1, b + n + 1, greater<int>());
    sort(c + 1, c + n + 1, greater<int>());

    priority_queue<Node> pq;
    pq.push(Node(1, 1, 1));
    map<Node, bool> vis;

    int cnt = 0;
    while (pq.size() && cnt <= k) {
        Node t = pq.top();
        pq.pop();

        if (vis[t]) continue;
        vis[t] = true;
        ++cnt;
        if (cnt == k) {
            cout << t.val << endl;
            return;
        }
    
        if (t.i < n) pq.push(Node(t.i + 1, t.j, t.k));
        if (t.j < n) pq.push(Node(t.i, t.j + 1, t.k));
        if (t.k < n) pq.push(Node(t.i, t.j, t.k + 1));
    }
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