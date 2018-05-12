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
	~TArrayHash();

	bool IsFull() { return dataCount == size; }

	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);

	void Reset();
	bool IsEnd();
	void GoNext();

	TRecord<TKey, TValue> GetCurrent();
	void SetCurrValue(TValue val);

	void Print();
	void PrintAll();

	friend char *GetString(string str);
};



//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TArrayHash<TKey, TValue>::TArrayHash(int _size) {
	size = _size;
	step = 13;
	arr = new TRecord<TKey, TValue>[size];
	for (int i = 0; i < size; i++) {
		arr[i].key = "";
	}
}

template <class TKey, class TValue>
TArrayHash<TKey, TValue>::~TArrayHash() {
	delete[] arr;
}

template <class TKey, class TValue>
bool TArrayHash<TKey, TValue>::Find(TKey fkey) {
	currNum = HashFunc(fkey) % size;
	int freepos = -1;

	for (int i = 0; i < size; i++) {
		efficiency++;

		if (arr[currNum].key == "") {
			if (freepos == -1) {
				return false;
			}
			else {
				currNum = freepos;
				return false;
			}
		}

		if (arr[currNum].key == fkey) {
			return true;
		}

		if ((freepos == -1) && (arr[currNum].key == "&")) {
			freepos = currNum;
		}

		currNum = (currNum + step) % size;
	}
	return false;
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::Insert(TRecord<TKey, TValue> rec) {
	if (!Find(rec.key)) {
		arr[currNum] = rec;
		dataCount++;
	}
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::Delete(TKey dkey) {
	if (Find(dkey)) {
		arr[currNum].key = "&";
		dataCount--;
	}
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::Reset() {
	currNum = 0;
	while (((arr[currNum].key == "&") || (arr[currNum].key == "")) && (currNum < size)) {
		currNum++;
	}
}

template <class TKey, class TValue>
bool TArrayHash<TKey, TValue>::IsEnd() {
	return currNum >= size;
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::GoNext() {
	while ((++currNum < size)) {
		if (((arr[currNum].key != "&") && (arr[currNum].key != "")))
			break;
		//currNum++;
	}
}

template <class TKey, class TValue>
TRecord<TKey, TValue> TArrayHash<TKey, TValue>::GetCurrent() {
	if (currNum < 0 || currNum >= size)
		throw "Current number is incorrect";
	return arr[currNum];
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::SetCurrValue(TValue val) {
	arr[currNum].value = val;
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::Print() {
	TRecord<TKey, TValue> tmp;
	int i = 0;
	for (Reset(); !IsEnd(); GoNext()) {
		tmp = GetCurrent();
		cout << currNum << ") " << GetString(tmp.key) << " - " << tmp.value << endl;
		//if(currNum < size - 1)
		//currNum++;
	}
}

template <class TKey, class TValue>
void TArrayHash<TKey, TValue>::PrintAll() {
	TRecord<TKey, TValue> tmp;
	for (int i = 0; i < size; i++) {
		currNum = i;
		tmp = GetCurrent();
		cout << currNum << ") " << GetString(tmp.key) << " - " << tmp.value << endl;
		//if(currNum < size - 1)
		//currNum++;
	}
}

char *GetString(string str) {
	int len = str.length();
	char *res = new char[len + 1];
	for (int i = 0; i < len; i++) {
		res[i] = str[i];
	}
	res[len] = '\0';
	return res;
}
