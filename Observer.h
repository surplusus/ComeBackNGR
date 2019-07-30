#pragma once
#include "stdafx.h"
#include "Scene.h"

class HandlerFunctionBase
{
public:
	void Exec() {
		Call();
	}
private:
	virtual void Call() = 0;
};

template<typename T>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::*MemberFunction)();
public:
	MemberFunctionHandler(T* inst, MemberFunction MF) :
		_instance(inst), _Function(MF) {}

	void Call() {
		(_instance->*_Function)();
	}
private:
	T* _instance;
	MemberFunction _Function;
};

class EventBus
{
public :
	// TakeOn(this,함수이름) 이렇게 쓴다
	template<typename T>
	void TakeOn(T* inst, void (T::*memFunc)()) {
		_passengers.emplace_back(new MemberFunctionHandler<T>(inst,memFunc));
	}
	void GetOff() {
		if (_passengers.size() == 0)		return;
		for (auto &p : _passengers) {
			p->Exec();
			delete p;
		}
		_passengers.clear();
	}
private:
	//std::map<std::type_index, MemberFunctionHandler*> _subscribers;
	std::vector<HandlerFunctionBase*> _passengers;
};