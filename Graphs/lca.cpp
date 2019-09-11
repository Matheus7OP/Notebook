/*
 * Matheus Oliveira
 * 18/11/2017
 * lca.cpp
*/
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN
 
vector< int > graph[MAXN];
int parents[MAXN], ancestors[MAXN][50], visited[MAXN], nodes, levels[MAXN];
 
void dfs(int node) {
	int i, qtdFilhos = graph[node].size(), filho;
 
	if( visited[node] == 1 ) return;
	visited[node] = 1;
 
	for(i=0; i < qtdFilhos; i++) {
		filho = graph[node][i];
 
		if( visited[filho] == 0 ) {
			parents[filho] = node;
			levels[filho] = levels[node] + 1;
			dfs(filho);
		}
	}
}
 
void build() {
	int i, j, lg;

	for( lg=1; (1 << lg) <= nodes; lg++);
	lg--;
 
	for(i=0; i <= nodes; i++) {
		for(j=0; j <= lg; j++) ancestors[i][j] = -1;
	}
 
	for(i=1; i <= nodes; i++) ancestors[i][0] = parents[i];
 
	for(j=1; j <= lg; j++) {
		for(i=1; i <= nodes; i++) {
			if( ancestors[i][j-1] != -1 ) {
				ancestors[i][j] = ancestors[ ancestors[i][j-1] ][j-1];
			}
		}
	}
}
 
int lca(int u, int v) {
	if( levels[u] < levels[v] ) swap(u, v);
	
	int lg, i;
	for(lg=1; (1 << lg) <= levels[u]; lg++);
	lg--;
 
	for(i=lg; i >= 0; i--) {
		if( ancestors[u][i] != -1 ) {
			if( levels[ ancestors[u][i] ] >= levels[v] ) {
				u = ancestors[u][i];
			}
		}
	}
 
	if(u == v) return u;
 
	for(i=lg; i >= 0; i--) {
		if(ancestors[u][i] != -1 and ancestors[v][i] != ancestors[u][i]) {
			u = ancestors[u][i];
			v = ancestors[v][i];
		}
	}
 
	return parents[u];
}