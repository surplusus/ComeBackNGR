#include "stdafx.h"
#include "ChainResponsibility.h"
#include "Basic_Value.h"
using std::make_pair;

int Chain::AddNextSuccessor(Chain *s, int id)
{
	if (successor.find(id) == successor.end())
		successor[id] = s;
	else
		successor[id]->AddNextSuccessor(s, id);

	countChainNum++;

	return countChainNum;
}

void Chain::OperateChain(int id)
{
	WhatToOperateWithChainID(id);
	
	successor[id]->OperateChain(id);
}
