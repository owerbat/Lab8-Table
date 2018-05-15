#pragma once
#include "Table.h"
#include <stack>

template <class TKey, class TValue>
class TNode {
public:
	TRecord<TKey, TValue> record;
	TNode<TKey, TValue> *pLeft, *pRight;
	int balance;

	TNode() {
		record = new TRecord<TKey, TValue>();
		pLeft = pRight = nullptr;
		balance = 0;
	}

	TNode(TRecord<TKey, TValue> _record, TNode<TKey, TValue> *_pLeft = nullptr, TNode<TKey, TValue> *_pRight = nullptr) {
		record = _record;
		pLeft = _pLeft;
		pRight = _pRight;
	}
};

template <class TKey, class TValue>
class TTreeTable : public TTable<TKey, TValue> {
protected:
	TNode<TKey, TValue> *pRoot, *pCurr;
	TNode<TKey, TValue> **pRes;
	stack<TNode<TKey, TValue> *> st;
public:
	TTreeTable();

	bool IsFull() { return false; }

	bool Find(TKey fkey);
	void Insert(TRecord<TKey, TValue> rec);
	void Delete(TKey dkey);

	void Reset();
	bool IsEnd();
	void GoNext();

	TRecord<TKey, TValue> GetCurrent() { return pCurr->record; }
	void SetCurrValue(TValue val) { pCurr->record.value = val; }
};



//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------



template <class TKey, class TValue>
TTreeTable<TKey, TValue>::TTreeTable() {
	pRoot = nullptr;
	pCurr = nullptr;
	pRes = nullptr;
}

template <class TKey, class TValue>
bool TTreeTable<TKey, TValue>::Find(TKey fkey) {
	pRes = &pRoot;

	while (*pRes != nullptr) {
		efficiency++;

		if ((*pRes)->record.key == fkey) {
			return true;
		}
		else if ((*pRes)->record.key < fkey) {
			pRes = &((*pRes)->pRight);
		}
		else {
			pRes = &((*pRes)->pLeft);
		}
	}

	return false;
}

template <class TKey, class TValue>
void TTreeTable<TKey, TValue>::Insert(TRecord<TKey, TValue> rec) {
	if (!Find(rec.key)) {
		*pRes = new TNode<TKey, TValue>(rec); // DANGER
	}
}

template <class TKey, class TValue>
void TTreeTable<TKey, TValue>::Delete(TKey dkey) {
	if (Find(dkey)) {
		TNode<TKey, TValue> *dnode = *pRes;

		if (dnode->pLeft == nullptr) {
			*pRes = dnode->pRight;
		}
		else if (dnode->pRight == nullptr) {
			*pRes = dnode->pLeft;
		}
		else {
			TNode<TKey, TValue> *curr = dnode->pLeft;
			TNode<TKey, TValue> **prev = &(dnode->pLeft);

			while (curr->pRight) {
				prev = &(curr->pRight);
				curr = curr->pRight;
			}

			dnode->record = curr->record;
			dnode = curr;
			*prev = curr->pLeft;
		}

		delete dnode;
	}
}

template <class TKey, class TValue>
void TTreeTable<TKey, TValue>::Reset() {

}

template <class TKey, class TValue>
bool TTreeTable<TKey, TValue>::IsEnd() {
	return (bool)(rand() % 2);
}

template <class TKey, class TValue>
void TTreeTable<TKey, TValue>::GoNext() {

}
