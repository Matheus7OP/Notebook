/*
 * Matheus Oliveira
 * 15/03/2018
 * 1464.cpp
*/
 
#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define MAXN 2010

struct GVector {
	int x, y;

	GVector(const int _x = 0, const int _y = 0) {
		this->x = _x;
		this->y = _y;
	}

	GVector operator-(const GVector &v) {
		GVector result;

		result.x = this->x - v.x;
		result.y = this->y - v.y;

		return result;
	}

	bool operator== (const GVector &v) const {
		return (this->x == v.x and this->y == v.y);
	}

	bool operator< (const GVector &v) const {
		if( v.x == this->x ) return this->y < v.y;
		return this->x < v.x;
	}

	int crossProduct(const GVector &v) {
		return ( (this->x * v.y) - (this->y * v.x) );
	}

} pivot, pontos[MAXN], pontosRestantes[MAXN], ch[MAXN];

int squareDist(GVector f, GVector s) {
	return ( (f.x - s.x)*(f.x - s.x) ) + ( (f.y - s.y)*(f.y - s.y) );
}

bool isCollinear(GVector a, GVector b, GVector c) {
	return (b - a).crossProduct(c - b) == 0;
}

bool compare(GVector first, GVector second) {
	if(first == pivot) return true;
	if(second == pivot) return false;

	GVector firstNormalizado = first - pivot, secondNormalizado = second - pivot;
	int produto = firstNormalizado.crossProduct(secondNormalizado);

	if( produto == 0 ) return squareDist(first, pivot) < squareDist(second, pivot);
	if( produto > 0 ) return true;
	return false;
}

GVector nextToLast(stack<GVector> &st) {
	GVector aux = st.top(), r;
	st.pop();

	r = st.top();
	st.push(aux);
	return r;
}

GVector last(stack<GVector> &st) {
	return st.top();
}

void findConvexHull(int n) {
	stack<GVector> convexHull;
	int indiceMenor = 0, qtdPontos = n, p;

	for(int i = 1; i < qtdPontos; i++) {
		if( pontos[i] < pontos[indiceMenor] ) indiceMenor = i;
	}

	pivot = pontos[indiceMenor];
	sort(pontos, pontos + qtdPontos, compare);

	for(int i = 0; i < 3; i++) convexHull.push( pontos[i] );

	p = 0;
	for(int i = 3; i < qtdPontos; i++) {
		GVector base = last(convexHull) - nextToLast(convexHull),
		novo = pontos[i] - last(convexHull);

		while( base.crossProduct(novo) < 0 and ((int) convexHull.size()) > 2 ) {
			pontosRestantes[p++] = convexHull.top();
			convexHull.pop();

			base = last(convexHull) - nextToLast(convexHull),
			novo = pontos[i] - last(convexHull);
		}
		convexHull.push(pontos[i]);
	}

	int w = 0;
	while( not convexHull.empty() ) {
		ch[w++] = convexHull.top();
		convexHull.pop();
	}
}