#pragma once
template <class T>
bool isPrime(T& n) {
	if (n % 3 == 0)
		return false;

	unsigned long long i = 5;

	while (i * i <= n) {
		if (n % i == 0 || n % (i + 2) == 0)
			return false;
		i = i + 6;
	}
	return true;
}