#include "ArrayTable.h"
#include "HashTable.h"
#include "TreeTable.h"
#include <fstream>

string RandomSrting(int size);

int main() {
	ifstream ifs("Machine_learning.txt");
	if (!ifs.is_open()) {
		cout << "Reading file error\n";
		return 1;
	}

	int count = 1000;
	char buffer[50];
	TScanTable<string, int> scantab(count);
	TSortTable<string, int> sorttab(count);
	TArrayHash<string, int> hashtab(count);
	TTreeTable<string, int> treetab;

	while (!ifs.eof()) {
		ifs >> buffer;
		string str(buffer);
		TRecord<string, int> tmp(str, 1);

		if (scantab.Find(tmp.key)) {
			scantab.SetCurrValue(scantab.GetCurrent().value + 1);
		}
		else {
			if (!scantab.IsFull()) {
				scantab.Insert(tmp);
			}
			else {
				cout << "Table size is too small!\n";
				return 1;
			}
		}

		if (sorttab.Find(tmp.key)) {
			sorttab.SetCurrValue(sorttab.GetCurrent().value + 1);
		}
		else {
			if (!sorttab.IsFull()) {
				sorttab.Insert(tmp);
			}
			else {
				cout << "Table size is too small!\n";
				return 1;
			}
		}

		if (hashtab.Find(tmp.key)) {
			hashtab.SetCurrValue(hashtab.GetCurrent().value + 1);
		}
		else {
			if (!hashtab.IsFull()) {
				hashtab.Insert(tmp);
			}
			else {
				cout << "Table size is too small!\n";
				return 1;
			}
		}

		if (treetab.Find(tmp.key)) {
			//treetab.SetCurrValue(treetab.GetCurrent().value + 1);
			treetab.SetResValue(treetab.GetResRecord().value + 1);
		}
		else {
			if (!treetab.IsFull()) {
				treetab.Insert(tmp);
			}
			else {
				cout << "Table size is too small!\n";
				return 1;
			}
		}
	}

	//scantab.Print();
	sorttab.Print();
	//hashtab.PrintAll();
	//treetab.Print();
	cout << endl;

	TRecord<string, int> maximum[10];
	TSortTable<int, string> top(count);

	for (sorttab.Reset(); !sorttab.IsEnd(); sorttab.GoNext()) {
		top.Insert(TRecord<int, string>(sorttab.GetCurrent().value, sorttab.GetCurrent().key));
	}

	for (top.Reset(); !top.TenRecordsLeft(); top.GoNext());

	int i = 0;
	while (!top.IsEnd()) {
		maximum[i] = TRecord<string, int>(top.GetCurrent().value, top.GetCurrent().key);
		i++;
		top.GoNext();
	}

	cout << "maximum:\n";
	for (i = 0; i < 10; i++) {
		maximum[i].Print();
		cout << endl;
	}

	ifs.close();
	
	return 0;
}



string RandomSrting(int size) {
	string res = "";
	for (int i = 0; i < size; i++) {
		res += (char)(rand() % 26 + 'a');
	}
	return res;
}
