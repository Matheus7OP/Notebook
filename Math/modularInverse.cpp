/*
 * Matheus Oliveira
 * 20/04/2018
 * modularInverse.cpp
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll modularInverse(ll a, ll m) {
	ll m0 = m;
	ll y = 0, x = 1;
	
	if(m == 1) return 0;
	
	ll q, t;
	while(a > 1) {
		q = a / m;
		t = m;
		
		m = a%m;
		a = t;
		t = y;
		
		y = x - q*y;
		x = t;
	}
	
	if(x < 0) x += m0;
	return x;
}

ll fastExpo(ll c, ll d, ll n) {
	if(d == 0) return 1;
	if(d == 1) return c;
	
	if(d%2 == 0) {
		ll res = fastExpo(c, d/2, n);
		return ((res%n) * (res%n)) % n;
	}
	return ((fastExpo(c, d-1, n) % n) * (fastExpo(c, 1, n) % n))%n;
}
