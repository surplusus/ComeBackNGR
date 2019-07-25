// context
class TCPstream;
class TCPState;

class TCPConnection
{
public:
	TCPConnection();

	void ActiveOpen();
	void PassiveOpen();
	void ProcessOctet(TCPstream*);
private:
	// State의 인터페이스가 friend이기 때문에 
	// State에서 TCPConnection의 함수를 사용할 권한이 있다
	friend class TCPState;
	void ChangeState(TCPState*);
private:
	TCPState* _state;
};

void TCPConnection::ActiveOpen()
{
	_state->ActiveOpen(this);
}

void TCPConnection::PassiveOpen()
{
	_state->PassiveOpen(this);
}

void TCPConnection::ChangeState(TCPState *s)
{
	_state = s;
}

// 상태 패턴 부모 클래스
class TCPState
{
	// 자식 클래스가 사용할 함수를 인터페이스에서 쓰이기위해
	// 클래스를 public으로 선언해 놓지만 구현은 자식들이 한다
public:
	virtual void ActiveOpen(TCPConnection*) {}
	virtual void PassiveOpen(TCPConnection*) {}
	virtual void Send(TCPConnection*) {}
	virtual void Transmit(TCPConnection*, TCPstream*) {}
protected:
	void ChangeState(TCPConnection*, TCPState*);
	
};

void TCPState::ChangeState(TCPConnection *t, TCPState *s)
{
	// context의 private friend로 State를 썼기 때문에 함수를 공유할 수 있다
	TCPConnection::ChangeState(s);
}

// concretes
class TCPestablished : public TCPState
{
	// 아마도 이 클래스는 싱클톤일듯
	// static으로 자신의 인스턴스를 참조할 수 있게 만들기위해서
public:
	static TCPState* Instance();

	virtual void Send(TCPConnection*);
	virtual void Transmit(TCPConnection*, TCPstream*);
		//...
};

class TCPclosed : public TCPState
{
public:
	// 아마도 이 클래스는 싱클톤일듯
// static으로 자신의 인스턴스를 참조할 수 있게 만들기위해서
	static TCPState* Instance();

	virtual void ActiveOpen(TCPConnection*);
	virtual void PassiveOpen(TCPConnection*);
	// ....
};

void TCPclosed::ActiveOpen(TCPConnection *t)
{
	TCPstream* stream;
	t->ProcessOctet(stream);
}

void TCPclosed::PassiveOpen(TCPConnection *t)
{
	ChangeState(t, TCPestablished::Instance());
}
