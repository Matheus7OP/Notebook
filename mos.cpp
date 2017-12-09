/*
 * Matheus Oliveira
 * 21/10/2017
 * 220B.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010

typedef pair<int, int> P;

int intervalo, freq[MAXN], tam, queries, i, elementos[MAXN], p1, p2, l, r, counter, ans[MAXN], ordem;

bool compare(pair<P, int> f, pair<P, int> s) {
	if(f.first.first/intervalo == s.first.first/intervalo) return f.first.second < s.first.second;
	return f.first.first/intervalo < s.first.first/intervalo;
}

int main() {
	scanf("%d %d", &tam, &queries);
	intervalo = sqrt(tam);

	for(i=0; i < tam; i++) scanf("%d", &elementos[i]);
	vector< pair< P, int > > mos;

	for(i=0; i < queries; i++) {
		scanf("%d %d", &l, &r);
		mos.push_back( make_pair( make_pair(l-1, r-1), i ) );
	}

	sort(mos.begin(), mos.end(), compare);

	p1 = p2 = counter = 0;

	if(elementos[p1] < MAXN) {
		freq[ elementos[p1] ]++;
		if( freq[ elementos[p1] ] == elementos[p1] ) counter++;
	}

	for(i=0; i < queries; i++) {
		l = mos[i].first.first, r = mos[i].first.second, ordem = mos[i].second;

		// movimento do primeiro ponteiro
		while(p1 < l) {
			if(elementos[p1] < MAXN) {
				if( freq[ elementos[p1] ] == elementos[p1] ) counter--;
				freq[ elementos[p1] ]--;
				if( freq[ elementos[p1] ] == elementos[p1] ) counter++;
			}

			p1++;
		}
		while(p1 > l) {
			p1--;

			if(elementos[p1] < MAXN) {
				if( freq[ elementos[p1] ] == elementos[p1] ) counter--;
				freq[ elementos[p1] ]++;
				if( freq[ elementos[p1] ] == elementos[p1] ) counter++;
			}
		}

		//movimento do segundo ponteiro
		while(p2 < r) {
			p2++;

			if(elementos[p2] < MAXN) {
				if( freq[ elementos[p2] ] == elementos[p2] ) counter--;
				freq[ elementos[p2] ]++;
				if( freq[ elementos[p2] ] == elementos[p2] ) counter++;
			}
		}
		while(p2 > r) {
			if(elementos[p2] < MAXN) {
				if( freq[ elementos[p2] ] == elementos[p2] ) counter--;
				freq[ elementos[p2] ]--;
				if( freq[ elementos[p2] ] == elementos[p2] ) counter++;
			}

			p2--;
		}

		ans[ordem] = counter;
	}

	for(i=0; i < queries; i++) printf("%d\n", ans[i]);

	return 0;
}