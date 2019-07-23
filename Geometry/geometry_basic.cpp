/*
 * Matheus Oliveira
 * 26/02/2018
 * geometry (basic structures and ops).cpp
*/

#include <algorithm>
using namespace std;

struct GVector {
	int x, y;

	GVector(int _x = 0, int _y = 0) {
		this->x = _x;
		this->y = _y;
	}

	GVector(GVector &a, GVector &b) {
		this->x = b.x - a.x;
		this->y = b.y - a.y;
	}

	GVector operator+(GVector &p) {
		GVector result;

		result.x = this->x + p.x;
		result.y = this->y + p.y;

		return result;
	}

	GVector operator*(int m) const {
		GVector result;

		result.x = x*m;
		result.y = y*m;

		return result;
	}

	bool operator==(GVector &p) {
		return (this->x == p.x and this->y == p.y);
	}

	// senO * |a| * |b|
	int crossProduct(GVector &v) {
		return ( (this->x * v.y) - (this->y * v.x) );
	}

	// cosO * |a| * |b|
	int dotProduct(GVector &v) {
		return ( (this->x * v.x) + (this->y * v.y) );
	}
};

struct Line {
	int A, B, C;

	Line(const GVector &p1, const GVector &p2) {
		// Ax + By = C general form
		this->A = (p2.y - p1.y); 
		this->B = (p2.x - p1.x) * (-1);
		this->C = (A * p1.x) + (B * p1.y);
	}

	bool hasPoint(const GVector &p) {
		return ( this->A*p.x + this->B*p.y == this->C );
	}
};

struct LineSegment {
	int A, B, C, xl, xr, yl, yr;

	LineSegment(GVector &p1, GVector &p2) {
		this->A = p2.y - p1.y;
		this->B = (p2.x - p1.x) * (-1);
		this->C = (p1.x * A) + (p1.y * B);

		this->xl = min(p1.x, p2.x);
		this->xr = max(p1.x, p2.x);

		this->yl = min(p1.y, p2.y);
		this->yr = max(p1.y, p2.y);
	}

	bool intersects(LineSegment &s) {
		// lembrar da manipulação de Ax + By = C para encontrar intersecções.
		// para o X, basta multiplicar B' "em cima" e por B "em baixo", de maneira a
		// subtrair a de cima da de baixo e isolar o X. Faz o mesmo para o Y.

		// são paralelos
		if( (this->A * s.B) - (this->B * s.A) == 0 ) return false;

		int x = ((this->C * s.B) - (this->B * s.C)) / ( (this->A * s.B) - (this->B * s.A) );
		int y = ((this->C * s.A) - (this->A * s.C)) / ( (this->B * s.A) - (this->A * s.B) );

		GVector intersec = GVector(x, y);
		GVector pl = GVector(xl, yl), pr = GVector(xr, yr);

		if( intersec == pl or intersec == pr ) return false;
		bool cond1, cond2;

		if( x >= this->xl and x <= this->xr and y >= this->yl and y <= this->yr ) cond1 = true;
		else cond1 = false;

		if( x >= s.xl and x <= s.xr and y >= s.yl and y <= s.yr ) cond2 = true;
		else cond2 = false;

		if(cond1 and cond2) return true;
		return false;
	}
};

// verifica se o ponto P está contido no triângulo ABC 
bool checaContinenciaEmTriangulo(GVector &a, GVector &b, GVector &c, GVector &p) {
	// para que p esteja em ABC, é necessário que o produto vetorial
	// AB x AP, BC x BP, CA x CP possua o mesmo sinal, isto é, os vetores possuem
	// o mesmo sentido.
	GVector ab = GVector(a, b), bc = GVector(b, c), ca = GVector(c, a);
	GVector ap = GVector(a, p), bp = GVector(b, p), cp = GVector(c, p);

	int s1, s2, s3;
	
	s1 = ab.crossProduct(ap);
	s2 = bc.crossProduct(bp);
	s3 = ca.crossProduct(cp);

	if(s1 > 0 and s2 > 0 and s3 > 0) return true;
	if(s1 < 0 and s2 < 0 and s3 < 0) return true;
	return false;
}