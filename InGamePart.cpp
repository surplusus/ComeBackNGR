#include "stdafx.h"
#include "InGamePart.h"
#include "ChainResponsibility.h"
#include "Collider.h"

InGamePart::InGamePart(PartsMgr *mgr, int x, int y) 
	: _partsManager(mgr), collider(mgr)
{
}
