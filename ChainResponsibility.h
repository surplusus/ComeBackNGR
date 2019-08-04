#pragma once

class Chain
	// id : 이벤트 종류를 enum으로 Basic_value에 정해놓았다
{
private:
	std::unordered_map<int, Chain*> successor;
	int countChainNum = 0;
public:
	Chain() {}
	virtual  ~Chain() = default;

	const int GetCountChainNum() const { return countChainNum; }
public:
	// 연쇄를 사용하기 위해 미리 순서 등록
	int AddNextSuccessor(Chain*, int);
	// 연쇄가 작동하였을때 각자 할 일 override해서 써야한다
	virtual void WhatToOperateWithChainID(int id) {}
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