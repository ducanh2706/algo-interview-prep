/*
Tag: Trie
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
#define st first
#define nd second
#define endl "\n"
#define all(v) v.begin(), v.end()
#define Unique(v) v.erase(unique(all(v)), v.end())

using namespace std;

struct Trie {
    Trie* c[26];
    bool hasX;
    int numY;

    Trie() {
        for (int i = 0; i < 26; i++) {
            c[i] = nullptr;
        }
        hasX = false;
        numY = 0;
    }
};

Trie *root = new Trie();


int numY = 0;

bool check(string &s) {
    Trie *x = root;
    for (auto &v : s) {
        int t = v - 'a';

        if (!x->c[t]) {
            return true;
        }

        x = x->c[t];
        if (x->hasX) return false;
    }
    return true;
}

void addX(string &s) {
    if (!check(s)) return;
    Trie *x = root;
    for (auto &v : s) {
        int t = v - 'a';
        if (!x->c[t]) {
            x->c[t] = new Trie();
        }
        x = x->c[t];
    }

    x->hasX = true;
    int del = x->numY;
    numY -= x->numY;
    
    x = root;
    for (auto &v : s) {
        int t = v - 'a';
        x = x->c[t];
        x->numY -= del;
    }
}

void addY(string &s) {
    Trie *x = root;
    if (!check(s)) return;
    for (auto &v : s) {
        int t = v - 'a';
        if (!x->c[t]) {
            x->c[t] = new Trie();
        }

        x = x->c[t];
        x->numY++;
    }
    numY++;
}



void PROGRAM(int _){
    int q;
    cin >> q;

    while (q--) {
        int t;
        string s;
        cin >> t >> s;
        if (t == 1) {
            addX(s);
        } else if (t == 2) {
            addY(s);
        }

        cout << numY << endl;
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