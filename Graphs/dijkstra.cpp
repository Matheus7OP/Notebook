/*
 * Matheus Oliveira
 * 11/02/2018
 * dijkstra.cpp
 *
 * Time Complexity: O(E * logV)
*/

#define mp make_pair
typedef pair<int, int> pii;

priority_queue< pii, vector< pii >, greater< pii > > dijkstra;
distances[node] = 0;
dijkstra.push( mp(0, node) );

while( not dijkstra.empty() ) {
	atual = dijkstra.top();
	dijkstra.pop();

	int actual = atual.second, dist = atual.first;
	if(distances[actual] < dist) continue;

	for(int i = 0; i < ((int) graph[actual].size()); i++) {
		int neighbor = graph[actual][i].second, d = graph[actual][i].first;

		if( distances[neighbor] > distances[actual] + d ) {
			distances[neighbor] = distances[actual] + d;
			dijkstra.push( mp(distances[neighbor], neighbor) );
		} 
	}
}