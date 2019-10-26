#include <iostream>

using namespace std;

int sum(int a, int b);

int main() {

	int a = 6; 
	int b = 5;
	cout << sum(a,b) << endl;

return 0;
}

int sum(int a, int b) {
	return a + b;
}

