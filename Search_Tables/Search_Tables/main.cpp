#include "ArrayTable.h"
#include "HashTable.h"
#include "TreeTable.h"
#include <time.h>

int main() {
	//srand(time(NULL));
	int m = 10, n = m + 10;
	TScanTable<int, int> t(n);
	TSortTable<int, int> s(n);

	for (int i = 0; i < m; i++) {
		TRecord<int, int> tmp1(rand() % 1000, rand() % 1000), tmp2(rand() % 1000, rand() % 1000);
		if(!t.IsFull())
			t.Insert(tmp1);
		if(!s.IsFull())
			s.Insert(tmp2);
	}

	s = t;

	cout << "t:\n";
	t.Print();
	cout << "\ns:\n";
	s.Print();
	
	return 0;
}
