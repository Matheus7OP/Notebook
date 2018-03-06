/*
 * Matheus Oliveira
 * 03/12/2017
 * dinic.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 5010
#define INF 1e9
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

struct edge {
	long long from, to, capacity, flow, rev;
}edges[4 * 30010];

vector<int> graph[MAXN];
queue<int> q;

int levels[MAXN], nodes, esize = 0, start[MAXN];

void addEdge(int u, int v, long long capacity) {
	edge e1 = {(long long)u, (long long)v, capacity, 0, (long long)esize + 1};
	edge e1Rev = {(long long)v, (long long)u, 0, 0, (long long)esize};

	graph[u].push_back( esize );
	edges[esize++] = e1;

	graph[v].push_back( esize );
	edges[esize++] = e1Rev;

	edge e2 = {(long long)v, (long long)u, capacity, 0, (long long)esize + 1};
	edge e2Rev = {(long long)u, (long long)v, 0, 0, (long long)esize};

	graph[v].push_back( esize );
	edges[esize++] = e2;

	graph[u].push_back( esize );
	edges[esize++] = e2Rev;
}

bool bfs(int source, int sink) {
	int i, atual, neighbor;
	for(i=1; i <= nodes; i++) levels[i] = -1;
	levels[source] = 0;

	q.push( source );
	while( not q.empty() ) {
		atual = q.front();
		q.pop();

		for(i=0; i < graph[atual].size(); i++) {
			int edgeId = graph[atual][i];
			neighbor = edges[edgeId].to;

			if(levels[neighbor] == -1 and edges[edgeId].flow < edges[edgeId].capacity) {
				levels[neighbor] = levels[atual] + 1;
				q.push(neighbor);
			}
		}
	}

	return (levels[sink] != -1);
}

long long sendFlow(int atual, long long flow, int sink) {
	if(atual == sink) return flow;
	if(!flow) return 0;

	int i;
	long long flowAtual, tentativa;
 
	for(; start[atual] < graph[atual].size(); start[atual]++) {
		i = start[atual];
		int edgeId = graph[atual][i];
		edge e = edges[edgeId];

		if(levels[ e.to ] == (levels[atual] + 1) and e.flow < e.capacity ) {
			flowAtual = min( flow, e.capacity - e.flow );

			// tento enviar flow desse node até a sink;
			tentativa = sendFlow( e.to, flowAtual, sink );

			if(tentativa > 0) {
				// já que foi possível passar fluxo, incremento o flow da aresta
				edges[ edgeId ].flow += tentativa;

				// e decrementa na reversa
				edges[ e.rev ].flow -= tentativa;
				return tentativa;
			}
		}
	}

	return 0;
}

long long dinic(int source, int sink) {
	long long maxFlow = 0, flow;

	while( bfs(source, sink) ) {
		memset(start, 0, sizeof start);
		while(true) {
			flow = sendFlow(source, INF, sink);
			//printf("flow = %lld\n", flow);
			if( flow == 0 ) break;
			maxFlow += flow;
		}
	}

	return maxFlow;
}


int main() {
	int n1, n2, e, i;
	long long int cap;

	scanf("%d %d", &nodes, &e);

	for(i=0; i < e; i++) {
		scanf("%d %d %lld", &n1, &n2, &cap);

		if(n1 == n2) continue;
		addEdge(n1, n2, cap);
	}

	printf("%lld\n", dinic(1, nodes));
	return 0;
}