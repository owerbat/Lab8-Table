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

	int GetSize() { return size; }
	int GetCurrNum() { return currNum; }
	TRecord<TKey, TValue> GetArrElem(int n) { return arr[n]; }

	void Reset() { currNum = 0; }
	bool IsEnd() { return currNum == dataCount; }
	void GoNext() { currNum++; }

	bool IsFull() { return size == dataCount; }

	bool TenRecordsLeft() { return currNum == (dataCount - 10); }
};

template <class TKey, class TValue>
class TSortTable;

template <class TKey, class TValue>
class TScanTable : public TArrayTable<TKey, TValue> {
public:
	TScanTable(int _size = 1) : TArrayTable<TKey, TValue>(_size) {}
	TScanTable(const TSortTable<TKey, TValue> &tab);

	TScanTable<TKey, TValue>& operator=(TSortTable<TKey, TValue> &tab);

	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);
};

template <class TKey, class TValue>
class TSortTable : public TArrayTable<TKey, TValue> {
public:
	TSortTable(int _size = 1) : TArrayTable<TKey, TValue>(_size) {}
	TSortTable(const TScanTable<TKey, TValue> &tab);

	TSortTable<TKey, TValue>& operator=(TScanTable<TKey, TValue> &tab);

	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);

	void QSort(int left, int right);
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

	return *this;
}



//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TScanTable<TKey, TValue>::TScanTable(const TSortTable<TKey, TValue> &tab) {
	size = tab.size;
	dataCount = tab.dataCount;
	currNum = tab.currNum;
	arr = new TRecord<TKey, TValue>[size];
	for (int i = 0; i < dataCount; i++) {
		arr[i] = tab.arr[i];
	}
}

template <class TKey, class TValue>
TScanTable<TKey, TValue>& TScanTable<TKey, TValue>::operator=(TSortTable<TKey, TValue> &tab) {
	if (size != tab.GetSize() /*tab.size*/) {
		//size = tab.size;
		size = tab.GetSize();
		delete[] arr;
		arr = new TRecord<TKey, TValue>[size];
	}
	//dataCount = tab.dataCount;
	dataCount = tab.GetDataCount();
	//currNum = tab.currNum;
	currNum = tab.GetCurrNum();
	arr = new TRecord<TKey, TValue>[size];
	for (int i = 0; i < dataCount; i++) {
		//arr[i] = tab.arr[i];
		arr[i] = tab.GetArrElem(i);
	}

	return *this;
}

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
		arr[currNum] = arr[dataCount - 1];
		dataCount--;
		efficiency++;
	}
}



//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TSortTable<TKey, TValue>::TSortTable(const TScanTable<TKey, TValue> &tab) {
	size = tab.size;
	dataCount = tab.dataCount;
	currNum = tab.currNum;
	arr = new TRecord<TKey, TValue>[size];
	for (int i = 0; i < dataCount; i++) {
		arr[i] = tab.arr[i];
	}
	QSort(0, dataCount - 1);
}

template <class TKey, class TValue>
TSortTable<TKey, TValue>& TSortTable<TKey, TValue>::operator=(TScanTable<TKey, TValue> &tab) {
	if (size != tab.GetSize() /*tab.size*/) {
		//size = tab.size;
		size = tab.GetSize();
		delete[] arr;
		arr = new TRecord<TKey, TValue>[size];
	}
	//dataCount = tab.dataCount;
	//currNum = tab.currNum;
	dataCount = tab.GetDataCount();
	currNum = tab.GetCurrNum();
	for (int i = 0; i < dataCount; i++) {
		//arr[i] = tab.arr[i];
		arr[i] = tab.GetArrElem(i);
	}
	QSort(0, dataCount - 1);

	return *this;
}

template <class TKey, class TValue>
bool TSortTable<TKey, TValue>::Find(TKey fkey) {
	int left = 0, right = dataCount - 1, mid;

	while (left <= right) {
		efficiency++;
		mid = (left + right) / 2;
		if (fkey == arr[mid].key) {
			currNum = mid;
			return true;
		}
		else if (fkey > arr[mid].key) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	currNum = left;
	return false;
}

template <class TKey, class TValue>
void TSortTable<TKey, TValue>::Insert(TRecord<TKey, TValue> rec) {
	if (!Find(rec.key)) {
		for (int i = dataCount; i > currNum; i--) {
			efficiency++;
			arr[i] = arr[i - 1];
		}
		arr[currNum] = rec;
		dataCount++;
	}
}

template <class TKey, class TValue>
void TSortTable<TKey, TValue>::Delete(TKey dkey) {
	if (Find(dkey)) {
		for (int i = currNum; i < dataCount - 1; i++) {
			efficiency++;
			arr[i] = arr[i + 1];
		}
		dataCount--;
	}
}

template <class TKey, class TValue>
void TSortTable<TKey, TValue>::QSort(int left, int right) {
	int mid = (left + right) / 2;
	TKey x = arr[mid].key;
	TRecord<TKey, TValue> tmp;
	int i = left, j = right;

	while (i <= j) {
		while (arr[i].key < x) {
			i++;
			efficiency++;
		}
		while (arr[j].key > x) {
			j--;
			efficiency++;
		}

		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}

		if (j > left) {
			QSort(left, j);
		}
		if (i < right) {
			QSort(i, right);
		}
	}
}
