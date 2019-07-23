/*
 * Matheus Oliveira
 * 10/11/2017
 * tdkprime.cpp
*/
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAXN 5000000
#define MAXX 87000000
 
unsigned long primos[MAXN+5];
vector<bool> is_prime (MAXX, true);
 
void crivo() {
	register unsigned long long i, j, counter = 0;
    primos[counter++] = 2;
 
	for(i=3; i <= MAXX; i += 2) {
		if(is_prime[i]) {
			primos[counter++] = i;
			if(counter == MAXN) break;
			for(j = i*i; j <= MAXX; j += i) is_prime[j] = false;
 
		}
	}
}