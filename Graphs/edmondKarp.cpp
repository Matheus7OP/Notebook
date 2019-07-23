/*
 * Matheus Oliveira
 * 29/11/2017
 * edmondKarp.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 150
#define INF 1e9

int source = 'A', sink = 'Z';
int capacities[MAXN][MAXN], visited[MAXN], from[MAXN];

queue<int> bfs;
vector<int> graph[MAXN];

int findPath() {
	memset(visited, 0, sizeof visited);
	memset(from, -1, sizeof from);

	while(not bfs.empty()) bfs.pop();
	int i, qtdN, atual, neighbor, previous;

	bfs.push(source);
	bool endWhile = false;

	while( not bfs.empty() ) {
		atual = bfs.front();
		bfs.pop();

		if(visited[atual]) continue;
		visited[atual] = 1;

		qtdN = graph[atual].size();

		for(i=0; i < qtdN; i++) {
			neighbor = graph[atual][i];

			if(visited[neighbor] == 0 and capacities[atual][neighbor] > 0) {
				from[neighbor] = atual;
				bfs.push(neighbor);

				if(neighbor == sink) {
					endWhile = true;
					break;
				}
			}
		}

		if(endWhile) break;
	}

	atual = sink;
	int minPath = INF;

	while( from[atual] != -1 ) {
		previous = from[atual];

		minPath = min(minPath, capacities[previous][atual]);
		atual = previous;
	}

	if(minPath == INF) return 0;

	atual = sink;
	while( from[atual] != -1 ) {
		previous = from[atual];

		capacities[previous][atual] -= minPath;
		capacities[atual][previous] += minPath;

		atual = previous;
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
	int linhas, i, j, peso, node1, node2, maxF;
	char n1, n2;

	scanf("%d", &linhas);
	getchar();

	for(i=0; i < linhas; i++) {
		scanf("%c %c %d", &n1, &n2, &peso);
		getchar();

		node1 = n1;
		node2 = n2;

		graph[node1].push_back(node2);
		graph[node2].push_back(node1);

		capacities[node1][node2] += peso;
		capacities[node2][node1] += peso;
	}

	printf("%d\n", maxFlow());
	return 0;
}