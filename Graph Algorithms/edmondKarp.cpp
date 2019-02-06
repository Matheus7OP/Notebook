/*
 * Matheus Oliveira
 * 29/11/2017
 * edmondKarp.cpp
 * 
 * Max flow using Edmonds Karp algorithm.
 * Time complexity: O(V*E²)
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
#define MAXN 150

int capacities[MAXN][MAXN], visited[MAXN], from[MAXN];
vector<int> graph[MAXN];

int source = 'A', sink = 'Z';
queue<int> bfs;

int findPath() {
	memset(visited, 0, sizeof visited);
	memset(from, -1, sizeof from);

	while(not bfs.empty()) bfs.pop();
	int i, qtdN, actual, neighbor, previous;

	bfs.push(source);
	bool endWhile = false;

	while( not bfs.empty() ) {
		actual = bfs.front();
		bfs.pop();

		if(visited[actual]) continue;
		visited[actual] = 1;

		qtdN = graph[actual].size();

		for(i=0; i < qtdN; i++) {
			neighbor = graph[actual][i];

			if(visited[neighbor] == 0 and capacities[actual][neighbor] > 0) {
				from[neighbor] = actual;
				bfs.push(neighbor);

				if(neighbor == sink) {
					endWhile = true;
					break;
				}
			}
		}

		if(endWhile) break;
	}

	actual = sink;
	int minPath = INF;

	while( from[actual] != -1 ) {
		previous = from[actual];

		minPath = min(minPath, capacities[previous][actual]);
		actual = previous;
	}

	if(minPath == INF) return 0;

	actual = sink;
	while( from[actual] != -1 ) {
		previous = from[actual];

		capacities[previous][actual] -= minPath;
		capacities[actual][previous] += minPath;

		actual = previous;
	}

	return minPath;
}

int maxFlow() {
	int maxF = 0, flow;

	while(true) {
		flow = findPath();

		if(flow == 0) break;
		maxF += flow;
	}

	return maxF;
}

int main() {
	int lines, i, j, c, node1, node2, maxF;
	char n1, n2;

	scanf("%d", &lines);
	getchar();

	for(i=0; i < lines; i++) {
		scanf("%c %c %d", &n1, &n2, &c);
		getchar();

		node1 = n1;
		node2 = n2;

		graph[node1].push_back(node2);
		graph[node2].push_back(node1);

		capacities[node1][node2] += c;
	}

	printf("%d\n", maxFlow());
	return 0;
}