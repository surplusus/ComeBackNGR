#include "stdafx.h"
#include "ChainResponsibility.h"
#include "Basic_Value.h"
using std::make_pair;

int Chain::AddNextSuccessor(Chain *s, int id)
{
	successor.insert(make_pair(id, s));

	return successor.count(id);
}

void Chain::OperateChain(int id)
{
	OperatePartOfChain(id);
	// 어떻게 해야되는거지비????
	Successor->OperateChain(id);
}
