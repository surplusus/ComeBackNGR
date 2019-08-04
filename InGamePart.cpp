#include "stdafx.h"
#include "InGamePart.h"
#include "ChainResponsibility.h"
#include "Collider.h"

InGamePart::InGamePart(PartsMgr *mgr, int x = 0, int y = 0) 
	: _partsManager(mgr), collider(mgr)
{
}
