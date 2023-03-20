// https://codeforces.com/contest/1185/problem/E

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

template<typename T> void smin(T &x, T y) {
    x = min(x, y);
}

template<typename T> void smax(T &x, T y) {
    x = max(x, y);
}

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

template<typename T>
using oset = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

const ll M = 1000000007;
const ll infll = M * M;

void io() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}

void io(string name) {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    io();
}

struct Z {
    int lx, rx, ty, by;

    bool operator==(const Z &rhs) const {
        return lx == rhs.lx &&
               rx == rhs.rx &&
               ty == rhs.ty &&
               by == rhs.by;
    }

    bool operator!=(const Z &rhs) const {
        return !(rhs == *this);
    }
};

Z D{M, -M, -M, M};

bool intersect(int x, int y, const Z & a, const Z & b) {
    return  a.lx <= x && x <= a.rx && a.by <= y && y <= a.ty && b.lx <= x && x <= b.rx && b.by <= y && y <= b.ty;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    vector<Z> e(26, D);
    F0R(i, n) cin >> g[i];
    F0R(i, n) {
        F0R(j, m) {
            if (g[i][j] == '.') continue;
            auto & c = e[g[i][j]-'a'];
            smin(c.lx, i);
            smax(c.rx, i);
            smax(c.ty, j);
            smin(c.by, j);
        }
    }
    int X = -1, Y = -1, cnt = 0;
    R0F(i, 26) {
        if (e[i] != D && X == -1) {
            X = e[i].lx;
            Y = e[i].ty;
            cnt = i+1;
        }
        if (e[i] == D) {
            if (X != -1) e[i] = {X, X, Y, Y};
            continue;
        }
        if (e[i].lx == e[i].rx) {
            int x= e[i].lx;
            FOR(y, e[i].by, e[i].ty+1) {
                if (g[x][y] != i + 'a' && g[x][y] != '*') {
                    cout << "NO\n";
                    return;
                }
                g[x][y] = '*';
            }
        } else if (e[i].by == e[i].ty) {
            int y = e[i].by;
            FOR(x, e[i].lx, e[i].rx+1) {
                if (g[x][y] != i + 'a' && g[x][y] != '*') {
                    cout << "NO\n";
                    return;
                }
                g[x][y] = '*';
            }
        } else {
            cout << "NO\n";
            return;
        }

    }
    cout << "YES\n";
    cout << cnt << '\n';
    F0R(i, cnt) {
        cout << e[i].lx+1 << ' ' << e[i].by+1 << ' ' << e[i].rx+1 << ' ' << e[i].ty+1 << '\n';
    }
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        solve();
    }
}