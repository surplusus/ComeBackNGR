#pragma once

class Scene
{
private:	//State pattern�� �� ����
	friend class GameCenter;
protected:	// scene���� �� ���� �� ������ ȣ��������
	void ChangeState(GameCenter*,Scene*);
};

