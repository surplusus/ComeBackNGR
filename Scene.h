#pragma once

class Scene
{
private:	//State pattern을 한 포석
	friend class GameCenter;
protected:	// scene에서 할 일이 다 끝나면 호출해주자
	void ChangeState(GameCenter*,Scene*);
};

