#include "stdafx.h"
#include "PartsMgr.h"

PartsMgr::PartsMgr(InGame *ingame)
{
	_callerAsScene = ingame;
}

PartsMgr::~PartsMgr()
{
}

void PartsMgr::Mediate(InGamePart *inputpart)
{
	if (inputpart == _parts[0])
	{
		// do something
	}
	else if (inputpart == _parts[1])
	{
		// do something
	}

}

