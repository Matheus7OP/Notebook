/*
 * Matheus Oliveira
 * 19/06/2020
 * Cute O(nlogn) LIS implementation
*/
 
#include <bits/stdc++.h>
using namespace std;

// this assumes no duplicates in array. Use multiset to allow duplicates
// answer is always s.size(). Remember that this set does not store correctly 
// all the elements of the answer, only its size.

int v[MAXN];

set<int> s;
set<int>::iterator it;

for(int i = 0; i < n; i++) {
    s.insert(v[i]);
    it = s.upper_bound(v[i]);
    if(it != s.end()) s.erase(it);
}

// for Longest Strictly Increasing Subsequence

multiset<int> s;
multiset<int>::iterator it;

for(int i = 0; i < n; i++) {
    s.insert(a[i]);
    it = s.lower_bound(a[i]);
    it++;
    if(it != s.end()) s.erase(it);
}