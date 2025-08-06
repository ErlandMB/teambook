void IS_BRIDGE(int v,int to); // some function to process the found bridge
ll n; // number of nodes
vvl adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
vl subsize;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    subsize[v] = 1;
    bool parent_skipped = false;
    for (int to : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            subsize[v] += subsize[to];
            if (low[to] > tin[v]) {
                IS_BRIDGE(v, to);
                ll a = subsize[to];
                ll b = n - a;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    subsize.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
