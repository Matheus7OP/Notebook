/*
 * Matheus Oliveira
 * 06/12/2017
 * quest4.cpp
 * Max Cardinality Bipartite Matching
*/
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN
 
vector<int> graph[MAXN];
 
set<int> set1, set2;
set<int>::iterator it;
 
int match[MAXN + 220], visited[MAXN];
 
int aug(int node) {
	if(visited[node]) return 0;
	visited[node] = 1;
	int i, neighbor;
 
	for(i=0; i < graph[node].size(); i++) {
		neighbor = graph[node][i];
 
		if( match[neighbor] == -1 or aug(match[neighbor]) ) {
			match[neighbor] = node;
			return 1;
		}
	}
 
	return 0;
}
 
int main() {
	int n, counter, n1, n2, mcbm, shiftSet2 = 200;
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		scanf("%d %d", &n1, &n2);
		graph[n1].push_back(n2 + shiftSet2);
		
		set1.insert(n1);
		set2.insert(n2);
	}

	mcbm = 0;
	memset(match, -1, sizeof match);

	for(it = set1.begin(); it != set1.end(); ++it) {
		memset(visited, 0, sizeof visited);
		mcbm += aug( (*it) );
	}
	
	printf("%d\n", mcbm);
	return 0;
}