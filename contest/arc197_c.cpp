/*
Tag: 
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
#define st first
#define nd second
#define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;

const int MAXN = 3e6 + 5;
const int MAX_BIT = 22;

bool vis[MAXN];

struct Trie {
    Trie* child[2];
    int cnt;

    Trie() {
        child[0] = child[1] = nullptr;
        cnt = 0;
    }
};

void add(Trie *root, int val) {
    Trie *x = root;
    for (int i = MAX_BIT - 1; i >= 0; i--) {
        int key = val >> i & 1;
        if (x->child[key] == nullptr) {
            x->child[key] = new Trie();
        }
        x = x->child[key];
        x->cnt++;
    }
}


void initTrie(Trie *root) {
    for (int i = 1; i < MAXN; i++) {
        add(root, i);
    }
}

void del(Trie *root, int val) {
    Trie *x = root;
    for (int i = MAX_BIT - 1; i >= 0; i--) {
        int key = val >> i & 1;
        x = x->child[key];
        x->cnt--;
    }
}

int query(Trie *root, int k) {
    int ans = 0;
    Trie *x = root;
    for (int i = MAX_BIT - 1; i >= 0; i--) {
        if (x->child[0]) {
            if (x->child[0]->cnt >= k) {
                x = x->child[0];
            }
            else {
                if (x->child[1] == nullptr) {
                    return ans;
                }
                ans += (1 << i);
                k -= x->child[0]->cnt;
                x = x->child[1];
            }
        }
        else if (x->child[1]) {
            ans += (1 << i);
            x = x->child[1];
        }
        else {
            return ans;
        }
    }
    return ans;
}


Trie *root = new Trie();
int q;

void PROGRAM(int _){
    initTrie(root);
    
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (a < MAXN && !vis[a]) {
            for (int i = a; i < MAXN; i += a) {
                if (!vis[i]) {
                    del(root, i);
                    vis[i] = true;
                }
            }
        }

        cout << query(root, b) << endl;
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