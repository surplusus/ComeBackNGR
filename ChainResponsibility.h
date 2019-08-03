#pragma once

class Chain
{
private:
	std::multimap<int, Chain*> successor;
	Chain* curChain;
public:
	Chain() : curChain(this) {}
	virtual  ~Chain() = default;
public:
	// ���⸦ ����ϱ� ���� �̸� �ؾ��� ��
	int AddNextSuccessor(Chain*, int);
	// ���Ⱑ �۵��Ͽ����� �� �� override�ؼ� ����Ѵ�
	virtual void OperatePartOfChain(int id) {}
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