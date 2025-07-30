// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=en

// Bellman Ford's ALgorithm 

// basically = relax all E edges V - 1 times
ll s = 0 // source
vl dist(n, INF); dist[s] = 0;                  // INF = 1e9 here
for (int i = 0; i < n - 1; ++i) {                // total O(V*E)
  bool modified = false;                       
  for (int u = 0; u < n; ++u)                  // these two loops = O(E)
    if (dist[u] != INF)                        // important check
      for (auto &[v, w] : adj[u]) {            
        if (dist[u] + w >= dist[v]) continue;  // not improving, skip
        dist[v] = dist[u] + w;                 // relax operation
        modified = true;                       
      }
  if (!modified) break;                        
}

bool hasNegativeCycle = false;
for (int u = 0; u < n; ++u)                    // one more pass to check
  if (dist[u] != INF)
    for (auto &[v, w] : adj[u])                
      if (dist[v] > dist[u] + w)                 // should be false
        hasNegativeCycle = true;               // if true => negative cycle
printf("Negative Cycle Exist? %s\n", hasNegativeCycle ? "Yes" : "No");

if (!hasNegativeCycle)
  for (int u = 0; u < n; ++u)
    printf("SSSP(%d, %d) = %d\n", s, u, dist[u]);

