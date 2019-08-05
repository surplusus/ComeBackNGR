#include "stdafx.h"
#include "InGamePart.h"
#include "ChainResponsibility.h"
#include "Collider.h"
#include "Basic_Value.h"

InGamePart::InGamePart(PartsMgr *mgr, int x, int f) 
	: _partsManager(mgr), collider(mgr)
{
	floor = f;
	pos.x = x;
	pos.y = f;
}