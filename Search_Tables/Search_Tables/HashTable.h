#pragma once
#include "Table.h"

template <class TKey, class TValue>
class THashTable : public TTable<TKey, TValue> {
protected:
	int HashFunc(TKey k) {
		int hash = 0;
		for (int i = 0; i < k.length(); i++) {
			hash += k[i] << i;
		}
		return hash;
	}
};

template <class TKey, class TValue>
class TArrayHash : public THashTable<TKey, TValue> {
protected:
	int size;
	int step;
	int currNum;
	TRecord<TKey, TValue> *arr;
public:
	TArrayHash(int _size = 100);
	TArrayHash();

	bool IsFull() { return dataCount == size; }

	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);

	void Reset();
	bool IsEnd();
	void GoNext();

	TRecord<TKey, TValue> GetCurrent();
	void SetCurrValue(TValue val);
};
