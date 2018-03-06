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