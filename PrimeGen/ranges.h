#pragma once
#include <vector>
using namespace std;

template <class T>
struct Range {
	T min;
	T max;
};


template <class T>
vector<Range<T>> splitinrange(T start, T end, unsigned int chunks) {
	vector<Range<T>> results(chunks);
	
	long long split = (end - start) / chunks;
	long long last = 0;
	for (unsigned int i = 1; i < chunks+1; i++) {
		Range<T> a;
		a.min = last;
		a.max = i * split;

		results[i - 1] = a;
		last = i * split;
	}


	return results;
}