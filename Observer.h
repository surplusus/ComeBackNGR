#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>

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
//public:
//	void Publish(T* inst) {
//		HandlerList* handlers = _subscribers[typeid(inst)];
//		if (!handlers)	return;
//		for (auto &handler : *handlers)
//			if (handler)	handler->Exec();
//	}
//	template<typename T, typename EventType>
//	void Subscribe(T* instance, void (T::*memberFunction)(EventType)) {
//		HandlerList *handlers = _subscribers[typeid(EventType)];
//		// first Initialization
//		if (!handlers) {
//			handlers = new HandlerList();
//			_subscribers[typeid(EventType)] = handlers;
//		}
//		handlers->emplace_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
//	}
public :
	// TakeOn(this,�Լ��̸�) �̷��� ����
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