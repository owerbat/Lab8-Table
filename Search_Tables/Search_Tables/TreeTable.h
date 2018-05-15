#pragma once
#include "Table.h"
#include <stack>

template <class TKey, class TValue>
class TNode {
	TRecord<TKey, TValue> record;
	TNode *pLeft, pRight;
	int balance;
};

template <class TKey, class TValue>
class TTreeTable : public TTable<TKey, TValue> {
protected:
	TNode *pRoot, *pCurr;
	TNode **pRes;
	stack<TNode *> st;
public:
	virtual bool Find(TKey fkey);
	virtual void Insert(TRecord<TKey, TValue> rec);
	virtual void Delete(TKey dkey);

	virtual void Reset();
	virtual bool IsEnd();
	virtual void GoNext();

	virtual TRecord<TKey, TValue> GetCurrent() { return pCurr->record; }
	virtual void SetCurrValue(TValue val) { pCurr->record.value = val; }
};
