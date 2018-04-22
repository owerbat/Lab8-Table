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

	TRecord<TKey, TValue> GetCurrent();

	void Reset() { currNum = 0; }
	bool IsEnd() { return size == dataCount; }
	void GoNext() { currNum++; }
};
