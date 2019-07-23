/*
 * Matheus Oliveira
 * 21/01/2018
 * floydWarshall.cpp
 * 
 * O(N^3) algorithm to find shortest path between every pair of nodes in a given graph
*/

for(int k = 0; k < n; k++) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			distancia[i][j] = min(distancia[i][j], distancia[i][k] + distancia[k][j]);
		}
	}
}
