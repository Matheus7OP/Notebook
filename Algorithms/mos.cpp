/*
 * Matheus Oliveira
 * 21/10/2017
 *
 * Example of offline query processing using "Mo's algorithm" to reduce as much as possible 
 * the number of movements the two pointers does.
 * 
 * Code shown here was used to solve: https://codeforces.com/problemset/problem/221/D
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
typedef pair<int, int> P;

int freq[MAXN], elements[MAXN], ans[MAXN];
int intervalo, tam, queries, i, p1, p2, l, r, counter, ordem;

bool compare(pair<P, int> f, pair<P, int> s) {
	if(f.first.first/intervalo == s.first.first/intervalo) return f.first.second < s.first.second;
	return f.first.first/intervalo < s.first.first/intervalo;
}

int main() {
	scanf("%d %d", &tam, &queries);
	intervalo = sqrt(tam);

	for(i=0; i < tam; i++) scanf("%d", &elements[i]);
	vector< pair< P, int > > mos;

	for(i=0; i < queries; i++) {
		scanf("%d %d", &l, &r);
		mos.push_back( make_pair( make_pair(l-1, r-1), i ) );
	}

	sort(mos.begin(), mos.end(), compare);
	p1 = p2 = counter = 0;

	if(elements[p1] < MAXN) {
		freq[ elements[p1] ]++;
		if( freq[ elements[p1] ] == elements[p1] ) counter++;
	}

	for(i=0; i < queries; i++) {
		l = mos[i].first.first, r = mos[i].first.second, ordem = mos[i].second;

		// movimento do primeiro ponteiro
		while(p1 < l) {
			if(elements[p1] < MAXN) {
				if( freq[ elements[p1] ] == elements[p1] ) counter--;
				freq[ elements[p1] ]--;
				if( freq[ elements[p1] ] == elements[p1] ) counter++;
			}

			p1++;
		}
		while(p1 > l) {
			p1--;

			if(elements[p1] < MAXN) {
				if( freq[ elements[p1] ] == elements[p1] ) counter--;
				freq[ elements[p1] ]++;
				if( freq[ elements[p1] ] == elements[p1] ) counter++;
			}
		}

		//movimento do segundo ponteiro
		while(p2 < r) {
			p2++;

			if(elements[p2] < MAXN) {
				if( freq[ elements[p2] ] == elements[p2] ) counter--;
				freq[ elements[p2] ]++;
				if( freq[ elements[p2] ] == elements[p2] ) counter++;
			}
		}
		while(p2 > r) {
			if(elements[p2] < MAXN) {
				if( freq[ elements[p2] ] == elements[p2] ) counter--;
				freq[ elements[p2] ]--;
				if( freq[ elements[p2] ] == elements[p2] ) counter++;
			}

			p2--;
		}

		ans[ordem] = counter;
	}

	for(i=0; i < queries; i++) printf("%d\n", ans[i]);
	return 0;
}