/*
 * Matheus Oliveira
 * 15/08/2018
 * sqrtArray.cpp
*/

#include <bits/stdc++.h>
using namespace std;

#define mp(a, b) make_pair(a, b)
typedef pair<int, int> P;

int qtdBuckets;

struct Bucket {
	int maxVal;
	vector<int> elements;

	Bucket() { this->maxVal = -1; }

	int get(int pos) { return elements[pos]; }
	int size() { return ((int) elements.size()); }
	int getMax() { return this->maxVal; }

	void insert(int pos, int val) { 
		this->maxVal = max(this->maxVal, val);
		elements.insert(elements.begin() + pos, val);
	}
};

struct Container {
	vector<Bucket> buckets;

	void addBucket() { buckets.push_back( Bucket() ); }
	void addToBucket(int pos, int val) {
		P info = getInfo(pos);
		int idxBucket = info.first, posInBucket = info.second;

		// if a bucket is going to surpass size x, we split it
		// in this case, x is two times the actual quantity of buckets
		// a constante could be used, too
		if( buckets[idxBucket].size() == 2*qtdBuckets ) {
			Bucket b1 = Bucket(), b2 = Bucket();

			for(int i = 0; i < qtdBuckets; i++) b1.insert(i, buckets[idxBucket].get(i));
			for(int i = qtdBuckets; i < 2*qtdBuckets; i++) b2.insert(i - qtdBuckets, buckets[idxBucket].get(i));

			buckets.erase(buckets.begin() + idxBucket);
			buckets.insert(buckets.begin() + idxBucket, b2);
			buckets.insert(buckets.begin() + idxBucket, b1);

			qtdBuckets = ((int) buckets.size());
			addToBucket(pos, val);
		}
		else buckets[idxBucket].insert(posInBucket, val);
	}

	P getInfo(int pos) {
		// returns in which bucket 'pos' is and in which position
		// inside this bucket 'pos' is
		// <bucket, posInBucket>
		int qtd;

		for(int i = 0; i < ((int) buckets.size()); i++) {
			qtd = buckets[i].size();
			if(qtd <= pos) pos -= qtd;
			else return mp(i, pos);
		}

		int bs = ((int) buckets.size()) - 1;
		return mp(bs, buckets[bs].size());
	}

	int getRealPos(int bckt, int pos) {
		// returns index of 'pos' in the actual array
		int ans = 0;

		for(int i = bckt-1; i >= 0; i--) ans += ((int) buckets[i].size());
		ans += pos;
		
		return ans;
	}

	int query(int pos, int d) {
		P info = getInfo(pos);
		int bckt = info.first, posInBucket, desired;
		posInBucket = info.second;

		desired = buckets[bckt].get(posInBucket);
		desired += d+1;


		if( buckets[bckt].getMax() >= desired ) {
			for(int i = posInBucket-1; i >= 0; i--) {
				if(buckets[bckt].get(i) >= desired) return getRealPos(bckt, i);
			}
		}

		for(int i = bckt-1; i >= 0; i--) {
			if(buckets[i].getMax() < desired) continue;
			for(int j = buckets[i].size()-1; j >= 0; j--) {
				if(buckets[i].get(j) >= desired) return getRealPos(i, j);
			}
		}

		return -1;
	}

	void debug() {
		for(int i = 0; i < ((int) buckets.size()); i++) {
			for(int j = 0; j < ((int) buckets[i].size()); j++) printf("%d ", buckets[i].get(j));
			printf("]\n");
		}
	}
} container;

int main() {
	int n, queries, op, h, d, pos, bckt, ans, idx;
	scanf("%d", &n);


	// starting with one bucket
	container.addBucket();
	qtdBuckets = 1;
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &h);
		container.addToBucket(i, h);
	}

	scanf("%d", &queries);
	for(int i = 0; i < queries; i++) {
		scanf("%d %d %d", &op, &pos, &h);

		if(op == 0) container.addToBucket(pos, h);
		else {
			pos--;
			ans = container.query(pos, h) + 1;
			printf("%d\n", ans);
		}
	}
	
	return 0;
}