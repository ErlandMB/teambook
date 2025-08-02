// Give a rooted tree, find the Lowest Common Ancestor node
// of A and B.
// Tested https://cses.fi/problemset/task/1688/
vector<vector<ll>> up;
vector<ll> depth;
const int LOG = 18; // for 2e5
 
void init(vector<vector<ll>> children, ll n) {
    up.assign(LOG,vector<ll>(n,0));
    depth.assign(n,0);
    function<void(int)> dfs = [&](int x) {
        for (auto y : children[x]) {
            up[0][y] = x;
            depth[y] = depth[x] +1;
            dfs(y);
        }
    };
    int root = 0; dfs(root);

    for (int i = 1; i < LOG; i++)
        for (int j = 0; j < n; j++) 
            up[i][j] = up[i-1][up[i-1][j]];
}
 
ll kParent(ll x, ll k) {
    ll i = 0;
    while (k) {
        if (k & 1) x = up[i][x];
        k >>= 1;
        i++;
    }
    return x;
}
 
ll query(ll x, ll y) {
    if (depth[x] < depth[y]) swap(x, y);
    x = kParent(x, depth[x] - depth[y]);
    if (x == y) {
        return x;
    }
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][x] != up[i][y]) {
            x = up[i][x];
            y = up[i][y];
        }
    }
    return up[0][x];
}

void test_case() {
    ll n, q; cin >> n >> q;
    vvl children(n);
    for (int i = 1; i < n; i++) {
        ll p; cin >> p; p--;
        children[p].pb(i);
    }
    init(children, n);
    
    for (int i = 0; i < q; i++) {
        ll x, y;cin >> x >> y;
        x--,y--;
        cout << query(x, y) + 1 << "\n";
    }
}
