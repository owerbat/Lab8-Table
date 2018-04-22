#include "ArrayTable.h"

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

template <class TKey, class TValue>
TRecord<TKey, TValue> TArrayTable<TKey, TValue>::GetCurrent() {
	return arr[currNum];
}
