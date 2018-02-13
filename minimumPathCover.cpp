/*
 * Matheus Oliveira
 * 10/02/2018
 * 1208.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 3510
#define pb(a) push_back(a)

bool vis[MAXN];
int match[MAXN];
vector<int> graph[MAXN];

int aug(int node) {
	if(vis[node]) return 0;
	vis[node] = true;

	for(int i = 0; i < ((int) graph[node].size()); i++) {
		int neighbor = graph[node][i];
		if( aug( match[neighbor] ) or match[neighbor] == -1 ) {
			match[neighbor] = node;
			return 1;
		}
	}

	return 0;
}

int main() {
	int nodes, edges, n1, n2, counter;
	while( scanf("%d %d", &nodes, &edges) != EOF ) {
		for(int i = 1; i <= nodes+2000; i++) graph[i].clear();

		for(int i = 0; i < edges; i++) {
			scanf("%d %d", &n1, &n2);
			graph[n1].pb(n2 + 2000);
		}

		counter = 0;
		memset(match, -1, sizeof match);

		for(int i = 1; i <= nodes; i++) {
			memset(vis, false, sizeof vis);
			aug(i);
		}

		for(int i = 2001; i <= nodes+2000; i++) {
			if(match[i] == -1) counter++;
		}

		printf("%d\n", counter);
	}
	return 0;
}