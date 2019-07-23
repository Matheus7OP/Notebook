/*
 * Matheus Oliveira
 * 19:27:47 10/04/2019
 * 
 * Example of a problem solution using Sack/DSU on Trees.
 * Model problem (solved using this code): https://codeforces.com/contest/600/problem/E 
 *
 * Time complexity: O(n * logn)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100100
#define pb(a) push_back(a)
typedef long long ll;

ll ans[MAXN], globalAns, aux[MAXN];
int bigChild[MAXN], szstree[MAXN], colors[MAXN], freqColors[MAXN], maxFreq;

vector<int> graph[MAXN];

void preCalc(int node, int parent) {
	int child, sz = 1, maxC = 0;
	bigChild[node] = -1;

	for(int i = 0; i < ((int) graph[node].size()); i++) {
		child = graph[node][i];
		if(child != parent) {
			preCalc(child, node);

			if(szstree[child] > maxC) {
				maxC = szstree[child];
				bigChild[node] = child;
			}

			sz += szstree[child];
		}
	}

	szstree[node] = sz;
}

void updateAns(int color, int v) {
	aux[ freqColors[color] ] -= ((ll) color);
	if( aux[ freqColors[color] ] == 0 and freqColors[color] == maxFreq ) maxFreq -= 1;

	freqColors[color] += v;
	aux[ freqColors[color] ] += ((ll) color);

	maxFreq = max(maxFreq, freqColors[ color ]);
	globalAns = aux[maxFreq];
}

void smallDfs(int node, int parent, int v) {
	int neighbor;
	updateAns(colors[node], v);

	for(int i = 0; i < ((int) graph[node].size()); i++) {
		neighbor = graph[node][i];
		if(neighbor != parent and neighbor != bigChild[node]) smallDfs(neighbor, node, v);
	}
}

void solve(int node, int parent, bool keep) {
	int neighbor;
	for(int i = 0; i < ((int) graph[node].size()); i++) {
		neighbor = graph[node][i];
		if(neighbor != bigChild[node] and neighbor != parent) solve(neighbor, node, false);
	}
	
	if(bigChild[node] != -1) solve(bigChild[node], node, true);

	smallDfs(node, parent, 1);
	ans[node] = globalAns;

	bigChild[node] = -1;
	if(not keep) smallDfs(node, parent, -1);
}

int main() {
	int n, n1, n2;

	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &colors[i]);
		aux[0] += ((ll) colors[i]);
	}

	for(int i = 0; i < n-1; i++) {
		scanf("%d %d", &n1, &n2);

		graph[n1].pb(n2);
		graph[n2].pb(n1);
	}

	preCalc(1, -1);
	solve(1, -1, true);

	for(int i = 1; i <= n; i++) {
		if(i != 1) printf(" ");
		printf("%lld", ans[i]);
	}
	printf("\n");

	return 0;
}
