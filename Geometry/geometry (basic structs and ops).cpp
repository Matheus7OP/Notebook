/*
 * Matheus Oliveira
 * 26/02/2018
 * geometry (basic structures and ops).cpp
*/

struct MVector {
	int x, y;

	MVector( int _x = 0, int _y = 0 ) {
		this->x = _x;
		this->y = _y;
	}

	MVector operator+ (MVector p) {
		MVector result;

		result.x = this->x + p.x;
		result.y = this->y + p.y;

		return result;
	}

	MVector operator*(int m) const {
		MVector result;

		result.x = x*m;
		result.y = y*m;

		return result;
	}

	// senO * |a| * |b|
	int crossProduct(MVector v) {
		return ( (this->x * v.y) - (this->y * v.x) );
	}

	// cosO * |a| * |b|
	int dotProduct(MVector v) {
		return ( (this->x * v.x) + (this->y * v.y) );
	}
};

struct Line {
	int A, B, C;

	Line(const MVector &p1, const MVector &p2) {
		// Ax + By = C general form
		this->A = (p2.y - p1.y); 
		this->B = (p2.x - p1.x) * (-1);
		this->C = (A * p1.x) + (B * p1.y);
	}

	bool hasPoint(const MVector &p) {
		return ( this->A*p.x + this->B*p.y == this->C );
	}
};

struct LineSegment {
	int A, B, C, xl, xr, yl, yr;

	LineSegment(Point &p1 = nada, Point &p2 = nada) {
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

		int x = ((this->C * s.B) - (this->B * s.C)) / ( (this->A * s.B) - (this->B * s.A) ),
		y = ((this->C * s.A) - (this->A * s.C)) / ( (this->B * s.A) - (this->A * s.B) );

		Point intersec = Point(x, y);
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