/*
 * Matheus Oliveira
 * 16:35:50 24/08/2019
 * hld.cpp
 *
 * Using Heavy-light decomposition to answer queries on trees in O(nlog²n) time complexity
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 
#define MAXN 

vector<int> graph[MAXN];
int posInChain[MAXN], heads[MAXN], heavy[MAXN], pos;
int stree[4 * MAXN], levels[MAXN], sz[MAXN], parents[MAXN], values[MAXN], n;

void update(int id, int l, int r, int idx, int v) {
	if(l == r) stree[id] = v;
	else {
		int m = (l + r) >> 1;

		if(idx <= m) update(id*2, l, m, idx, v);
		else update(id*2+1, m+1, r, idx, v);

		stree[id] = max(stree[id*2], stree[id*2+1]);
	}
}

int queryStree(int id, int l, int r, int a, int b) {
	if( r < a or l > b ) return -INF;
	if( l >= a and r <= b ) return stree[id];
	
	int m = (l + r) >> 1;
	return max( queryStree(id*2, l, m, a, b), queryStree(id*2+1, m+1, r, a, b) );
}

int dfs(int node) {
	int neighbor, ans = 1, maxSz = -1, idx = -1;

	for(int i = 0; i < (int) graph[node].size(); i++) {
		neighbor = graph[node][i];
		if(neighbor == parents[node]) continue;

		parents[neighbor] = node;
		levels[neighbor] = levels[node] + 1;
		// values[neighbor] = graph[node][i].first; data on edges

		ans += dfs(neighbor);
		if(sz[neighbor] > maxSz) maxSz = sz[neighbor], idx = neighbor;
	}

	heavy[node] = idx;
	return sz[node] = ans;
}

void decompose(int node, int head) {
	heads[node] = head;
	posInChain[node] = pos++;

	if( heavy[node] != -1 ) {
		int neighbor;
		decompose(heavy[node], head);

		for(int i = 0; i < (int) graph[node].size(); i++) {
			neighbor = graph[node][i];
			if(neighbor != heavy[node] and neighbor != parents[node]) decompose(neighbor, neighbor);
		}
	}
}

int queryPath(int a, int b) {
	int ans = -1;

	while( heads[a] != heads[b] ) {
		if( levels[ heads[a] ] < levels[ heads[b] ] ) swap(a, b);
		ans = max(ans, queryStree(1, 1, n, posInChain[ heads[a] ], posInChain[a]));
		a = parents[ heads[a] ];
	}

	if( levels[a] < levels[b] ) swap(a, b);
	ans = max(ans, queryStree(1, 1, n, posInChain[b], posInChain[a]));
	// ans = max(ans, queryStree(1, 1, n, posInChain[ heavy[b] ], posInChain[a])); data on edges

	return ans;
}

void initialize() {
	levels[1] = 1;
	pos = 1;

	dfs(1);
	decompose(1, 1);

	for(int i = 1; i <= n; i++) update(1, 1, n, posInChain[i], values[i]);
}