#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <algorithm>
#include <vector>
#include "ranges.h"
#include <chrono>
#include <Windows.h>
#include "BetterIsPrime.h"
#include "getCustomThreadPriority.h"

#define used_type unsigned long long

using namespace std;

unsigned int counter = 0;
unsigned int primesfound = 0;

int threadP = THREAD_PRIORITY_NORMAL;
ofstream outFile;
mutex mu, mu2;
vector<used_type> p;

template <class T>
void log_result(T prime) {
	mu.lock();
	p.push_back(prime);
	primesfound++;
	mu.unlock();
}
void incrementCounter() {
	mu2.lock();
	counter++;
	mu2.unlock();
}

template <class T>
void primesThread(T min, T max) {


	SetThreadPriority(GetCurrentThread(), threadP);


	for (T i = min; i < max; i++) {
		if (IsPrime(i)) {
			log_result<T>(i);
		}
		incrementCounter();
	}
}

int main()
{
	short thread_count = std::thread::hardware_concurrency();
	if (thread_count % 2 != 0) {
		cout << "Odd number of cores.";
		return 1;
	}

	used_type max;
	cout << "how many iterations?: ";
	cin >> max;

	char choice;
	cout << "change thread priority? (y/n): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
		threadP = chooseThreadP();

	cout << "Thread priority is " << threadP << endl;
	vector<Range<used_type>> r = splitinrange<used_type>(0, max, thread_count);
	vector<thread> threads;



	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	cout << "Starting " << thread_count << " threads...";
	for (short i = 0; i < thread_count; i++)
		threads.push_back(
			thread(primesThread<used_type>, r[i].min, r[i].max)
		);

	cout << "Done" << endl
		<< "Waiting for threads to finish...";

	for (unsigned short i = 0; i < threads.size(); i++)
		threads[i].join();
	cout << "Done" << endl;

	chrono::steady_clock::time_point end = chrono::steady_clock::now();









	cout << "Completed " << counter << " iterations in " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl
		<< "Memory consumed by vector: " << sizeof(used_type) * p.size() << " bytes" << endl
		<< "Found " << primesfound << " prime numbers" << endl;

	cout << "Write to file? (y/n): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {

		cout << "Sorting...";

		sort(p.begin(), p.end());

		cout << "Done." << endl << "Writing to file 'primes.txt'...";
		outFile.open("primes.txt", ios::out);
		for (unsigned int i = 0; i < p.size(); i++) {
			outFile << p[i] << endl;
		}
		cout << " Done." << endl << endl;
	}
	outFile.close();
}