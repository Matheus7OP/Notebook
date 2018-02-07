/*
 * Matheus Oliveira
 * 21/01/2018
 * menorCaminho(p)
*/

// Floyd Warshall
for(int k = 0; k < n; k++) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			distancia[i][j] = min(distancia[i][j], distancia[i][k] + distancia[k][j]);
		}
	}
}

// Dijkstra
while( not pq.empty() ) {
	P atual = pq.top();
	pq.pop();

	int node = atual.first, dist = atual.second;
	if( vis[node] == 1 ) continue;
	vis[node] = 1;

	for(int i = 0; i < graph[node].size(); i++) {
		int neighbor = graph[node][i].second, d = graph[node][i].first;

		if(vis[neighbor] == 0 and distance[neighbor] > dist + d) {
			distance[neighbor] = dist+d;
			pq.push( mp(distance[neighbor], neighbor) );
		}
	}
}