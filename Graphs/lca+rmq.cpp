/*
 * Matheus Oliveira
 * 18/11/2017
 * 1476.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 20010
#define INF 1e9

typedef pair<int, int> P;

int parents[MAXN], rmq[MAXN][50], rank1[MAXN], ilhas, rmqParent[MAXN], levels[MAXN], ancestors[MAXN][50], pai[MAXN], visited[MAXN];
int aux;
vector<P> tree[MAXN];

// array parents sendo utilizado no union find. array pai sendo utilizado no lca.

int read(int node) {
	if( parents[node] == -1 ) return node;
	return parents[node] = read(parents[node]);
}

void join(int n1, int n2) {
	int s1 = read(n1), s2 = read(n2);
	if(s1 == s2) return;

	if(rank1[s1] > rank1[s2]) parents[s2] = s1;
	else {
		if(rank1[s2] > rank1[s1]) parents[s1] = s2;
		else {
			rank1[s2]++;
			parents[s1] = s2;
		}
	}
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

int main() {
	int edges, sedes, n1, n2, i, peso, j;

	pair<int, P> atual;
	priority_queue< pair<int, P> > kruskal;

	while(scanf("%d %d %d", &ilhas, &edges, &sedes) != EOF) {
		for(i=1; i <= ilhas; i++) {
			tree[i].clear();
			rmqParent[i] = INF;
			parents[i] = -1;
			visited[i] = 0;
			for(j=0; j < 50; j++) rmq[i][j] = -1, ancestors[i][j] = -1;
		}

		for(i=0; i < edges; i++) {
			scanf("%d %d %d", &n1, &n2, &peso);
			kruskal.push( make_pair( peso, make_pair(n1, n2) ) );
		}

		while(not kruskal.empty()) {
			atual = kruskal.top();
			kruskal.pop();

			n1 = atual.second.first, n2 = atual.second.second, peso = atual.first;

			if( read(n1) == read(n2) ) continue;
			join(n1, n2);

			tree[n1].push_back( make_pair(peso, n2) );
			tree[n2].push_back( make_pair(peso, n1) );
		}

		pai[1] = 1;
		levels[1] = 0;
		rmqParent[1] = INF;

		dfs(1);
		build();

		for(i=0; i < sedes; i++) {
			scanf("%d %d", &n1, &n2);
			printf("%d\n", rangeMinimum(n1, n2));
		}
	} 

	return 0;
}