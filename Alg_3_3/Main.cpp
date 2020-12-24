#include "Header.h"
#include <iomanip>
#include <iostream>
#include <locale>
#include <chrono>

using namespace std;

void main()
{
	Heap Heap;

	Heap.insert(4);
	Heap.insert(65);
	Heap.insert(16);
	Heap.insert(24);
	Heap.insert(89);
	Heap.insert(18);
	Heap.insert(892);
	Heap.insert(803);
	Heap.insert(749);
	cout << endl;

	Iterator* iterator;

	iterator = Heap.add_bft_iterator();
	while (iterator->has_next())
		cout << iterator->next() << " ";
	cout << endl;
	cout << endl;

	Iterator* iterator2;
	iterator2 = Heap.add_dft_iterator();
	while (iterator2->has_next())
		cout << iterator2->next() << " ";
	cout << endl << endl;

}

