// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=en

// Floyd-Warshall algorithm

for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (min_dist[i][k] < INF && min_dist[k][j] < INF) {
                    ll new_dist = min_dist[i][k] + min_dist[k][j];
                    if (new_dist < min_dist[i][j]) {
                        min_dist[i][j] = new_dist;
                    }
                }
            }
        }
}
// Given a directed or an undirected weighted graph G with n vertices. The task is to find the length of the shortest path between each pair of vertices i and j .
// Complexity -> O(n ^ 3)

// The graph may have negative weight edges, but no negative weight cycles.
