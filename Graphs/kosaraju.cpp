/*
 * Matheus Oliveira
 * 14:56:06 11/09/2019
 * kosaraju.cpp
 *
 * Way to find strongly connected components using only 2 DFS's.
 * Components will be stored in vector 'compo'
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 
#define MAXN 
#define pb push_back

stack<int> st;
vector<int> graph[MAXN], kosaraju[MAXN], compo;

int cnt;
bool vis[MAXN];

void dfs(int node, int op) {
	if(vis[node]) return;

	int neighbor;
	vis[node] = true;

	if(op == 1) {
		for(int i = 0; i < (int) graph[node].size(); i++) {
			neighbor = graph[node][i];
			kosaraju[neighbor].pb(node);
			if(not vis[neighbor]) dfs(neighbor, op);
		}

		st.push(node);
	}
	else {
		compo[cnt].pb(node);
		for(int i = 0; i < (int) kosaraju[node].size(); i++) {
			neighbor = kosaraju[node][i];
			if(not vis[neighbor]) dfs(neighbor, op);
		}
	}
}

// inside main
for(int i = 1; i <= n; i++) {
	if(not vis[i]) dfs(i, 1);
}

memset(vis, false, sizeof vis);

while( not st.empty() )	{
	if(not vis[ st.top() ]) {
		dfs( st.top(), 2 );
		cnt++;
	}
	st.pop();
}