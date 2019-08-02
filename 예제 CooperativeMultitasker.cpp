#include "stdafx.h"
#include "¿¹Á¦ CooperativeMultitasker.h"

unsigned int ProcessManager::UpdateProcesses(unsigned long deltaMs)
{
	unsigned short int successCount = 0;
	unsigned short int failCount = 0;

	ProcessList::iterator it = m_processList.begin();
	while (it != m_processList.end())
	{
		StrongProcessPtr pCurrProcess = (*it);

		ProcessList::iterator thisIt = it;
		++it;

		if (pCurrProcess->GetState() == Process::UNINITIALIZED)
			pCurrProcess->VOnInit();

		if (pCurrProcess->GetState() == Process::RUNNING)
			pCurrProcess->VOnUpdate(deltaMs);

		if (pCurrProcess->IsDead())
		{
			switch (pCurrProcess->GetState())
			{
				case Process::SUCCEEDED:
				{
					pCurrProcess->VOnSuccess();
					StrongProcessPtr pChild = pCurrProcess->removechild();
					if (pChild)
						AttachProcess(pChild);
					else
						++successCount;
					break;
				}
				case Process::FAILED:
				{
					pCurrProcess->VOnFail();
					++failCount;
					break;
				}
				case Process::ABORTED:
				{
					pCurrProcess->VOnAbort();
					++failCount;
					break;
				}
			}
			m_processList.erase(thisIt);
		}
	}
	return ((successCount<<16) | failCount);
}

