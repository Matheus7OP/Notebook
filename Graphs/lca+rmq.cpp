/*
 * Matheus Oliveira
 * 18/11/2017
 * 1476.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define INF
#define MAXN

typedef pair<int, int> pii;

vector<pii> tree[MAXN];
int aux;
int parents[MAXN], rmq[MAXN][50], rank1[MAXN], ilhas, rmqParent[MAXN], levels[MAXN], ancestors[MAXN][50], pai[MAXN], visited[MAXN];

// array parents sendo utilizado no union find. array pai sendo utilizado no lca.

int read(int node) {
	if( parents[node] == -1 ) return node;
	return parents[node] = read(parents[node]);
}

void join(int n1, int n2) {
	int s1 = read(n1), s2 = read(n2);
	
	if(s1 == s2) return;
	if(rank1[s1] < rank1[s2]) swap(s1, s2);

	parents[s2] = s1;
	rank1[s1] += rank1[s2] + 1;
}

void dfs(int node) {
	int i, noNeighbors = tree[node].size(), neighbor;

	if( visited[node] == 1 ) return;
	visited[node] = 1;

	for(i=0; i < noNeighbors; i++) {
		neighbor = tree[node][i].second;

		if(visited[neighbor] == 0) {
			rmqParent[neighbor] = tree[node][i].first;
			levels[neighbor] = levels[node] + 1;
			pai[neighbor] = node;

			dfs(neighbor);
		}
	} 
}

void build() {
	int i, j, lg;

	for(lg=1; (1 << lg) <= ilhas; lg++);
	lg--;

	for(i=1; i <= ilhas; i++) {
		rmq[i][0] = rmqParent[i], ancestors[i][0] = pai[i];
	}

	for(j=1; j <= lg; j++) {
		for(i=1; i <= ilhas; i++) {
			if(ancestors[i][j-1] != -1) {

				rmq[i][j] = min( rmq[ ancestors[i][j-1] ][j-1], rmq[i][j-1] );
				ancestors[i][j] = ancestors[ ancestors[i][j-1] ][j-1];
			}
		}
	}
}

int rangeMinimum(int u, int v) {
	if(levels[u] < levels[v]) swap(u, v);
	int i, j, lg, ans = INF;

	for(lg=1; (1 << lg) <= levels[u]; lg++);
	lg--;
	
	for(i=lg; i >= 0; i--) {
		if(ancestors[u][i] != -1) {
			if(levels[ ancestors[u][i] ] >= levels[v]) {
				if(u != 1) ans = min(ans, rmq[u][i]);
				u = ancestors[u][i];
			}
		}
	}

	aux = u;
	if(u == v) return ans;

	for(i=lg; i >= 0; i--) {
		if(ancestors[u][i] != -1 and ancestors[u][i] != ancestors[v][i]) {
			ans = min(ans, rmq[v][i]);
			ans = min(ans, rmq[u][i]);
			
			u = ancestors[u][i];
			v = ancestors[v][i];
		}
	}

	aux = ancestors[u][0];

	ans = min(ans, rmq[u][0]);
	ans = min(ans, rmq[v][0]);
	return ans;
}