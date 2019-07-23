/*
 * Matheus Oliveira e Doritos :D
 * 01/08/2018
 * primeFactorsLogN.cpp
*/

#include <bits/stdc++.h>
#define MAXX 87000000

using namespace std;
typedef long long ll;

vector<int> greaterFactor(MAXX, -1);

void crivo() {
	register unsigned long long i, j;
	greaterFactor[1] = 1;

	for(i=2 ; i < MAXX; i++) {
		if(greaterFactor[i] == -1) {
			greaterFactor[i] = i;
			for(j = i + i; j < MAXX; j += i) greaterFactor[j] = i;
		}
	}
}
 
vector<int> primeFactors(int n) {
	vector<int> ret;
	while(greaterFactor[n] != 1){
		ret.push_back(greaterFactor[n]);
		n /= greaterFactor[n];
	}
	return ret;
}

int main() {
	crivo();
	while(true){
		int n;
		scanf("%d", &n);
		vector<int> out = primeFactors(n);
		for(int i = 0; i < out.size(); i++) printf(" %d", out[i]);
		printf("\n");
	}
	return 0;
} 
