/*
 * Matheus Oliveira
 * 07/02/2018
 * hash.cpp
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

#define MAXN 15007

struct DoubleHash {
	ll powers1[MAXN], powers2[MAXN], values1[MAXN], values2[MAXN], prime1, prime2;
	int strSize;

	DoubleHash(const string &word, const ll base1 = 419, const ll base2 = 521, const ll prime1 = 82517999, const ll prime2 = 76824091) {
		precalcPowers(powers1, base1, prime1);
		precalcPowers(powers2, base2, prime2);

		precalcValues(values1, base1, prime1, powers1, word);
		precalcValues(values2, base2, prime2, powers2, word);

		this->strSize = ((int) word.size());
		this->prime1 = prime1;
		this->prime2 = prime2;
	}

	void precalcPowers(ll *powers, const ll base, const ll prime) {
		powers[0] = 1;
		for(int i = 1; i < MAXN; i++) {
			powers[i] = powers[i-1] * base;
			powers[i] %= prime;
		}
	}

	void precalcValues(ll *values, const ll base, const ll prime, ll *powers, const string &word) {
		int aux = ((int) word.size()) - 1;
		for(int i = ((int) word.size()); i >= 0; i--) {
			values[i] = ( word[i] + 307 ) + (values[i+1] * base);
			values[i] %= prime;
		}
	}

	P hashSubstr(int l, int r) {
		P h;	

		h.first = values1[l] - values1[r+1] * powers1[r - l + 1];
		h.first %= this->prime1;
		h.first += this->prime1;
		h.first %= this->prime1;

		h.second = values2[l] - values2[r+1] * powers2[r - l + 1];
		h.second %= this->prime2;
		h.second += this->prime2;
		h.second %= this->prime2;

		return h;
	}
};