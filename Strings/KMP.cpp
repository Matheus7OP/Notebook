/*
 * Matheus Oliveira
 * 15/02/2018
 * KMP.cpp
 * O(M+N)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN
int prefixVal[MAXN];

// prefixVal[i] armazena o valor do maior prefixo, até o index i, que também é sufixo da mesma substring [1, i]
void buildPrefixFunction(const string &word) {
	prefixVal[0] = prefixVal[1] = 0;
	int j;
	for(int i = 2; i <= ((int) word.size()); i++) {
		j = prefixVal[i-1];
		while(true) {
			if(word[i-1] == word[j]) {
				prefixVal[i] = j+1;
				break;
			}

			if(j == 0) {
				prefixVal[i] = 0;
				break;
			}

			j = prefixVal[j];
		}
	}
}

bool searchSubstr(const string &word, const string &pattern) {
	int i, j;
	i = j = 0;

	while(true) {
		if(j == ((int) word.size())) break;
		if(word[j] == pattern[i]) {
			i++;
			j++;
			if(i == ((int) pattern.size())) return true;
			continue;
		}

		if(i > 0) i = prefixVal[i];
		else j++;
	}

	return false;
}
