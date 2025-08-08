// Subtree queries
// https://cses.fi/problemset/task/1137
//
template <class T> class BIT {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	BIT(int size) : size(size), bit(size + 1), arr(size) {}

	void set(int ind, int val) { add(ind, val - arr[ind]); }

	void add(int ind, int val) {
		arr[ind] += val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] += val; }
	}

	T pref_sum(int ind) {
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}
};

ll n;
vvl adj;
vl tin, tout;
ll timer = 0;

void dfs(ll u, ll p) {
    tin[u] = timer++;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer;
}

void euler_tour(ll root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    dfs(root, -1);
}

void solve() {
    ll q; cin >> n >> q;
    vl v(n); cin >> v;
    adj.resize(n);
    forn (i, n - 1) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    euler_tour(0);
    BIT<ll> bit(n);
    forn (i, n) { bit.set(tin[i], v[i]); }
    while (q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll node, val; cin >> node >> val;
            bit.set(tin[node - 1], val);
        } else {
            ll node; cin >> node;
            node--;
            ll right = bit.pref_sum(tout[node] - 1);
            ll left;
            if (tin[node] == 0) {
                left = 0;
            } else {
                left = bit.pref_sum(tin[node] - 1);
            }
            cout << right - left << '\n';
        }
    }
}

int main() {
    fastIO;
    // cout << fixed;
    // cout << setprecision(10);
    // neighbors.assign(n, vll());
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}   
