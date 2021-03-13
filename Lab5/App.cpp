
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <cassert>
using namespace std;


int main() {
	
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}