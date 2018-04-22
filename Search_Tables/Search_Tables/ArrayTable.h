#pragma once
#include "Table.h"

template <class TKey, class TValue>
class TArrayTable :	public TTable<TKey, TValue> {
protected:
	TRecord<TKey, TValue> *arr;
	int size;
	int currNum;
public:
	TArrayTable(int _size = 1);
	TArrayTable(const TArrayTable<TKey, TValue> &tab);
	~TArrayTable();

	TArrayTable<TKey, TValue>& operator=(const TArrayTable<TKey, TValue> &tab);

	TRecord<TKey, TValue> GetCurrent() { return arr[currNum]; }
	void SetCurrValue(TValue val) { arr[currNum].value = val; }

	void Reset() { currNum = 0; }
	bool IsEnd() { return currNum == dataCount; }
	void GoNext() { currNum++; }

	bool IsFull() { return size == dataCount; }
};

template <class TKey, class TValue>
class TScanTable : public TArrayTable<TKey, TValue> {
	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);
};




//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TArrayTable<TKey, TValue>::TArrayTable(int _size) {
	size = _size;
	arr = new TRecord<TKey, TValue>[size];
}

template <class TKey, class TValue>
TArrayTable<TKey, TValue>::TArrayTable(const TArrayTable<TKey, TValue> &tab) {
	size = tab.size;
	arr = new TRecord<TKey, TValue>[size];
	for (int i = 0; i < size; i++) {
		arr[i] = tab.arr[i];
	}
}

template <class TKey, class TValue>
TArrayTable<TKey, TValue>::~TArrayTable() {
	delete[] arr;
}

template <class TKey, class TValue>
TArrayTable<TKey, TValue>& TArrayTable<TKey, TValue>::operator=(const TArrayTable<TKey, TValue> &tab) {
	if (size != tab.size) {
		size = tab.size;
		delete[] arr;
		arr = new new TRecord<TKey, TValue>[size];
	}
	for (int i = 0; i < size; i++) {
		arr[i] = tab.arr[i];
	}
}



//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
bool TScanTable<TKey, TValue>::Find(TKey fkey) {
	for (int i = 0; i < dataCount; i++) {
		efficiency++;
		if (arr[i].key == fkey) {
			currNum = i;
			return true;
		}
	}
	currNum = dataCount;
	return false;
}

template <class TKey, class TValue>
void TScanTable<TKey, TValue>::Insert(TRecord<TKey, TValue> rec) {
	if (!Find(rec.key)) {
		arr[currNum] = rec;
		dataCount++;
		efficiency++;
	}
}

template <class TKey, class TValue>
void TScanTable<TKey, TValue>::Delete(TKey dkey) {
	if (Find(dkey)) {
		arr[currNum] = arr[dataCount--];
		efficiency++;
	}
}
