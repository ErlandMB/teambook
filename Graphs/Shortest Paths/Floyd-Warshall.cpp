// Floyd-Warshall algorithm


for (int k = 0; k < n; k++) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			long long new_dist = min_dist[i][k] + min_dist[k][j];
			if (new_dist < min_dist[i][j]) {
				min_dist[i][j] = min_dist[j][i] = new_dist;
			}
		}
	}
  }
// Given a directed or an undirected weighted graph G with n vertices. The task is to find the length of the shortest path between each pair of vertices i and j .
// Complexity -> O(n ^ 3)

// The graph may have negative weight edges, but no negative weight cycles.
