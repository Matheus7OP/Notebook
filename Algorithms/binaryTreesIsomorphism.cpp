/*
 * Matheus Oliveira
 * 14/03/2018
 * Simple way to check if two given binary trees are isomorphic
*/
 
#include <bits/stdc++.h>
using namespace std;

vector<int> treeA[MAXN], treeB[MAXN];

bool iso(int nodeG, int nodeD) {
	if( ((int) treeA[nodeG].size()) == 0 and ((int)treeB[nodeD].size()) == 0 ) return true;
	if( treeA[nodeG].size() != treeB[nodeD].size() ) return false;

	if( ((int) treeA[nodeG].size()) == 1 ) return iso(treeA[nodeG][0], treeB[nodeD][0]);
	else {
		return ( (iso(treeA[nodeG][0], treeB[nodeD][0]) && iso(treeA[nodeG][1], treeB[nodeD][1])) or 
		(iso(treeA[nodeG][0], treeB[nodeD][1]) && iso(treeA[nodeG][1], treeB[nodeD][0])) );
	}
}