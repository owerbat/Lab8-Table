#include "ArrayTable.h"
#include "HashTable.h"
#include "TreeTable.h"
#include <time.h>

string RandomSrting(int size);

int main() {
	//srand(time(NULL));
	/*int m = 10, n = m + 10;
	TScanTable<int, int> t(n);
	TSortTable<int, int> s(n);
	int *keys1 = new int[n], *keys2 = new int[n];

	for (int i = 0; i < m; i++) {
		TRecord<int, int> tmp1(rand() % 1000, rand() % 1000), tmp2(rand() % 1000, rand() % 1000);
		keys1[i] = tmp1.key;
		keys2[i] = tmp2.key;
		if(!t.IsFull())
			t.Insert(tmp1);
		if(!s.IsFull())
			s.Insert(tmp2);
	}

	//s = t;

	cout << "t:\n";
	t.Print();
	cout << "\ns:\n";
	s.Print();

	t.Delete(keys1[9]);
	s.Delete(keys2[4]);

	cout << "t:\n";
	t.Print();
	cout << "\ns:\n";
	s.Print();*/
	

	/*int n = 20;
	TArrayHash<string, int> tab(n);
	string *keys = new string[n];

	for (int i = 0; i < n/2; i++) {
		TRecord<string, int> tmp(RandomSrting(5), rand() % 1000);
		keys[i] = tmp.key;
		if (!tab.IsFull()) {
			tab.Insert(tmp);
		}
	}

	cout << "tab:\n";
	tab.Print();
	cout << "\nall tab:\n";
	tab.PrintAll();

	tab.Delete(keys[0]);

	cout << "tab:\n";
	tab.Print();
	cout << "\nall tab:\n";
	tab.PrintAll();*/



	TTreeTable<int, int> tt;
	
	return 0;
}



string RandomSrting(int size) {
	string res = "";
	for (int i = 0; i < size; i++) {
		res += (char)(rand() % 26 + 'a');
	}
	return res;
}
