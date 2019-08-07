#pragma once
#include "stdafx.h"
#include "Basic_Value.h"

class IEvent
{
protected:
	EVENTTYPE eventmark = NONE;
	EVENTTYPE GetEventMark() { return eventmark; }
};

class HandlerFunctionBase {
public:
	void Exec(IEvent* evnt) {
		Call(evnt);
	}
private:
	virtual void Call(IEvent* evnt) = 0;
};

template<typename T, typename Type>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::*MemberFunction)(Type*);

	MemberFunctionHandler(T* inst, MemberFunction memberFunc)
		: _instance(inst), _memFunc(MemberFunction) {};

	void Call(IEvent* evnt) {
		(_instance->*_memFunc)(static_cast<Type*>(evnt));
	}
private:
	T* _instance;
	MemberFunction _memFunc;
};

typedef std::list<HandlerFunctionBase*> HandlerList;
class EventBus
{
public:
	template<typename Type>
	void Publish(Type* evnt) {
		HandlerList* handlers = subscribers[typeid(Type)];
		if (handlers == nullptr)
			return;
		for (auto &handler : *handlers) {
			if (handler != nullptr) {
				handler->Exec(evnt);
			}
		}
	}
	template<typename T, typename Type>
	 void Subscribe(T* inst, void (T::*memberFunction)(Type*)){
		HandlerList* handlers = subscribers[typeid(Type)];
		if (handlers == nullptr){
			handlers = new HandlerList();
			subscribers[typeid(Type)] = handlers;
		}
		handlers->push_back(new MemberFunctionHandler<T, Type>(inst, memberFunction));
	}
private:
	std::unordered_map<std::type_index, HandlerList*> subscribers;
};
