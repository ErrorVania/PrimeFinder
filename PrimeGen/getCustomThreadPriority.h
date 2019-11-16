#pragma once
#include <iostream>
using namespace std;
int chooseThreadP() {

	short i = 1;
	cout << "[1] Idle" << endl
		 << "[2] Lowest" << endl
		 << "[3] Below Normal" << endl
		 << "[4] Normal" << endl
		 << "[5] Above Normal" << endl
		 << "[6] Highest" << endl
		 << "[7] Time Critical" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
		case 1:
			return THREAD_PRIORITY_IDLE;
			break;
		case 2:
			return THREAD_PRIORITY_LOWEST;
			break;
		case 3:
			return THREAD_PRIORITY_BELOW_NORMAL;
			break;
		case 4:
			return THREAD_PRIORITY_NORMAL;
			break;
		case 5:
			return THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case 6:
			return THREAD_PRIORITY_HIGHEST;
			break;
		case 7:
			return THREAD_PRIORITY_TIME_CRITICAL;
			break;
		default:
			return THREAD_PRIORITY_NORMAL;
			break;
	}

}