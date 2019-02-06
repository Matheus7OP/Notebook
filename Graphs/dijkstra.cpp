/*
 * Matheus Oliveira
 * 11/02/2018
 * dijkstra.cpp
 * Time Complexity: O(E * logV)
*/

priority_queue< P, vector< P >, greater< P > > dijkstra;
distances[0] = 0;
dijkstra.push( mp(0, 0) );

while( not dijkstra.empty() ) {
	atual = dijkstra.top();
	dijkstra.pop();

	int nodeAtual = atual.second, dist = atual.first;
	
	if(vis[nodeAtual]) continue;
	vis[nodeAtual] = true;

	for(int i = 0; i < ((int) graph[nodeAtual].size()); i++) {
		int neighbor = graph[nodeAtual][i].second, d = graph[nodeAtual][i].first;

		if( !vis[neighbor] and distances[neighbor] > distances[nodeAtual] + d ) {
			distances[neighbor] = distances[nodeAtual] + d;
			dijkstra.push( mp(distances[neighbor], neighbor) );
		} 
	}
}