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
	// 연쇄를 사용하기 위해 미리 해야할 일
	int AddNextSuccessor(Chain*, int);
	// 연쇄가 작동하였을때 할 일 override해서 써야한다
	virtual void OperatePartOfChain(int id) {}
	// 연쇄 발동!!!
	virtual void OperateChain(int id);
};

//------------구체화 예시---------------//
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