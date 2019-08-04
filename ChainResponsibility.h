#pragma once

class Chain
	// id : �̺�Ʈ ������ enum���� Basic_value�� ���س��Ҵ�
{
private:
	std::unordered_map<int, Chain*> successor;
	int countChainNum = 0;
public:
	Chain() {}
	virtual  ~Chain() = default;

	const int GetCountChainNum() const { return countChainNum; }
public:
	// ���⸦ ����ϱ� ���� �̸� ���� ���
	int AddNextSuccessor(Chain*, int);
	// ���Ⱑ �۵��Ͽ����� ���� �� �� override�ؼ� ����Ѵ�
	virtual void WhatToOperateWithChainID(int id) {}
	// ���� �ߵ�!!!
	virtual void OperateChain(int id);
};

//------------��üȭ ����---------------//
class Handler1 : public Chain
{
public:
	/*virtual*/void handle(int i)
	{
		if (rand() % 3)
		{
			// 3. Don't handle requests 3 times out of 4
			std::cout << "H1 passed " << i << "  ";
			Chain::OperateChain(i); // 3. Delegate to the base class
		}
		else
			std::cout << "H1 handled " << i << "  ";
	}
};