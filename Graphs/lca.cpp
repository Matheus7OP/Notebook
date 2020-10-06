/*
 * Matheus Oliveira
 * 18/11/2017
 * lca.cpp
*/
 
#define MAXN
#define MAXL
 
vector<int> graph[MAXN];
int parents[MAXN], ancestors[MAXL][MAXN], n, levels[MAXN];
 
void dfs(int node, int parent) {
	for(int nb : graph[node]) {
		if(nb != parent) {
			parents[nb] = node;
			levels[nb] = levels[node] + 1;
			dfs(nb, node);
		}
	}
}
 
void build(int root) {
	dfs(root, -1);
	int lg;

	for(lg = 1; (1 << lg) <= n; lg++);
	lg--;
 
	for(int j = 0; j <= lg; j++) {
		for(int i = 1; i <= n; i++) ancestors[j][i] = -1;
	}
 
	for(int i = 1; i <= n; i++) ancestors[0][i] = parents[i];
 
	for(int j = 1; j <= lg; j++) {
		for(int i = 1; i <= n; i++) {
			if( ancestors[j-1][i] != -1 ) {
				ancestors[j][i] = ancestors[j-1][ ancestors[j-1][i] ];
				// rmq[i][j] = min( rmq[ ancestors[i][j-1] ][j-1], rmq[i][j-1] );
			}
		}
	}
}
 
int lca(int u, int v) {
	if( levels[u] < levels[v] ) swap(u, v);
	
	int lg;
	for(lg = 1; (1 << lg) <= levels[u]; lg++);
	lg--;
 
	for(int j = lg; j >= 0; j--) {
		if( ancestors[j][u] != -1 ) {
			if( levels[ ancestors[j][u] ] >= levels[v] ) {
				u = ancestors[j][u];
			}
		}
	}
 
	if(u == v) return u;
 
	for(int j = lg; j >= 0; j--) {
		if(ancestors[j][u] != -1 and ancestors[j][v] != ancestors[j][u]) {
			u = ancestors[j][u];
			v = ancestors[j][v];
		}
	}
 
	return parents[u];
}