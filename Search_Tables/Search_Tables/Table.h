#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class TKey, class TValue>
class TRecord {
public:
	TKey key;
	TValue value;

	TRecord();
	TRecord(TKey _key, TValue _value);
	TRecord(const TRecord<TKey, TValue> &rec);

	TRecord &operator=(const TRecord<TKey, TValue> &rec);

	void Print() { cout << key << " - " << value; }
};

template <class TKey, class TValue>
class TTable {
protected:
	int dataCount;
	int efficiency;
public:
	TTable() { dataCount = 0; efficiency = 0; }

	int GetDataCount() { return dataCount; }

	bool IsEmpty() { return dataCount == 0; }
	virtual bool IsFull() = 0;

	virtual bool Find(TKey fkey) = 0;
	virtual void Insert(TRecord<TKey, TValue> rec) = 0;
	virtual void Delete(TKey dkey) = 0;

	virtual void Reset() = 0;
	virtual bool IsEnd() = 0;
	virtual void GoNext() = 0;

	virtual TRecord<TKey, TValue> GetCurrent() = 0;
	virtual void SetCurrValue(TValue val) = 0;

	int GetEfficiency() { return efficiency; }

	void Print() {
		TRecord<TKey, TValue> tmp;
		int i = 0;
		for (Reset(); !IsEnd(); GoNext()) {
			tmp = GetCurrent();
			cout << i << ") "  << tmp.key << " - " << tmp.value << endl;
			i++;
		}
	}
};



//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TRecord<TKey, TValue>::TRecord() {
	key = TKey();
	value = TValue();
}

template <class TKey, class TValue>
TRecord<TKey, TValue>::TRecord(TKey _key, TValue _value) {
	key = _key;
	value = _value;
}

template <class TKey, class TValue>
TRecord<TKey, TValue>::TRecord(const TRecord<TKey, TValue> &rec) {
	key = rec.key;
	value = rec.value;
}

template <class TKey, class TValue>
TRecord<TKey, TValue> &TRecord<TKey, TValue>::operator=(const TRecord<TKey, TValue> &rec) {
	key = rec.key;
	value = rec.value;
	return *this;
}
