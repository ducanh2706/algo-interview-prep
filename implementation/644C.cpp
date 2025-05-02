/*
@notice: interview prep
@author: aaron
@source: https://codeforces.com/problemset/problem/644/C
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int Rand() {
    return uniform_int_distribution<int>(1, 1'000'000'000'000'000'000)(rng);
}

/*
Extract the "query" part.
For each path, hash all of its domain (can use hash xor)
Group by result of hash
*/

unordered_map<string, vector<int>> queries;
unordered_map<string, int> enc; // encode
unordered_map<string, unordered_map<int, bool>> in;
unordered_map<int, vector<string>> groups;


void PROGRAM(int _){
    int n;   cin >> n;

    enc[""] = Rand();

    while (n--) {
        string s;   cin >> s;
        int queryStart = s.find('/', 7);
        string hostname = s.substr(7, ((queryStart == -1) ? s.size() : queryStart) - 7);
        if (queryStart == -1) {
            unordered_map<int, bool> &i = in[hostname];
            if (i.find(enc[""]) == i.end()) {
                i[enc[""]] = true;
                queries[hostname].push_back(enc[""]);
            }
            continue;
        }

        string query = s.substr(queryStart, s.size());
        if (enc.find(query) == enc.end()) {
            enc[query] = Rand();
        }

        int queryEncode = enc[query];

        unordered_map<int, bool> &i = in[hostname];
        if (i.find(queryEncode) == i.end()) {
            i[queryEncode] = true;
            queries[hostname].push_back(queryEncode);
        }
    }

    auto hashXor = [&](vector<int> &val) {
        int res = 0;
        for (auto &v : val) {
            res ^= v;
        }
        return res;
    };

    int ans = 0;
    for (auto &str : queries) {
        int h = hashXor(str.nd);
        groups[h].push_back(str.st);
    }

    for (auto val : groups) {
        if (val.nd.size() >= 2) {
            ++ans;
        }
    }

    cout << ans << endl;

    string pref = "http://";

    for (auto val : groups) {
        if (val.nd.size() >= 2) {
            for (auto &str : val.nd) {
                cout << pref << str << " ";
            }
            cout << endl;
        }
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