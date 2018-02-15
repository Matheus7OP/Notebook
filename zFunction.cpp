/*
 * Matheus Oliveira
 * 15/02/2018
 * zFunction.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 2000010
int z[MAXN];

// z[i] armazena o tamanho da maior substring que se inicia em word[i] e que também é prefixo da string word
void calculateZ(const string &word) {
	int l = 0, r = 0, tam = ((int) word.size());
	z[0] = 0;

	for (int i = 1; i < tam; i++) {
		if (i > r) {
	    	l = r = i;
	    	while (r < tam && word[r-l] == word[r]) r++;
	   	 	z[i] = r-l; r--;
		} else {
		    int k = i-l;
		    if (z[k] < r-i+1) z[i] = z[k];
		    else {
		      l = i;
		      while (r < tam && word[r-l] == word[r]) r++;
		      z[i] = r-l; r--;
		    }
		}
	}
}
