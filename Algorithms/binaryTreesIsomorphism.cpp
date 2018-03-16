/*
 * Matheus Oliveira
 * 14/03/2018
 * C.cpp
*/
 
#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
vector<int> graph[MAXN], desired[MAXN];

bool iso(int nodeG, int nodeD) {
	//printf("checando %d e %d\n", nodeG, nodeD);
	if( ((int) graph[nodeG].size()) == 0 and ((int)desired[nodeD].size()) == 0 ) return true;
	if( graph[nodeG].size() != desired[nodeD].size() ) return false;

	if( ((int) graph[nodeG].size()) == 1 ) return iso(graph[nodeG][0], desired[nodeD][0]);
	else {
		return ( (iso(graph[nodeG][0], desired[nodeD][0]) && iso(graph[nodeG][1], desired[nodeD][1])) or 
		(iso(graph[nodeG][0], desired[nodeD][1]) && iso(graph[nodeG][1], desired[nodeD][0])) );
	}
}

int main() {
	int casos, n, pai, root, rootD;
	scanf("%d", &casos);

	while(casos--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			graph[i].clear();
			desired[i].clear();
		}

		for(int i = 1; i <= n; i++) {
			scanf("%d", &pai);

			if(pai == 0) { 
				root = i;
				continue;
			}
		
			graph[pai].push_back(i);
		}

		for(int i = 1; i <= n; i++) {
			scanf("%d", &pai);

			if(pai == 0) { 
				rootD = i;
				continue;
			}
			
			desired[pai].push_back(i);
		}

		if( iso(root, rootD) ) printf("1\n");
		else printf("0\n");
	}

	return 0;
}