#pragma once
#pragma region 클래스 선언부분
#include "Collider.h"
class Observer;
class InGame;
class InGamePart;
class Map;
class Monster;
class Prey;
class Obstacle;
class Neoguri;
//Event Class
class EventPreyRemove;
#pragma endregion
// mediator
class PartsMgr : public Observer
{
public:
	PartsMgr(InGame*);
	virtual ~PartsMgr();
protected:
	InGame* _callerAsScene;
	// part 마다 만들어야되지만
	// InGamePart에 각각 타입을 key로 값는 멀티맵을 써보았다
	// Draw()를 위해서 등록되어있는 key값을 vector로 가지고 있다
	std::unordered_map<std::string, std::shared_ptr<InGamePart>> _parts;
	std::list<std::shared_ptr<InGamePart>> _partsOrderList;
	bool isDrawOrderDirty = true;
	// 너구리의 현재좌표
	POINT _posNGR;
	// mon, ob, rey 갯수
	int cntMon = 0;
	int cntObs = 0;
	int cntPrey = 0;
	int numOfCurrentMap = 1;

	TimeMgr* timer = TimeMgr::GetInstance();
	
	virtual void AddMonster(int numOfFloorOn, int srtX, int endX, int dir);
	virtual void AddObstacle(int numOfFloorOn, int coordX);
	virtual void AddPrey(int numOfFloorOn, int coordX);
	virtual void AddMap(int num);
	std::string MakePartIndexName(const char name, int num = -1);
	void MakeDrawOrder();
	void MakeMonAndPreyByJSON();
public:
	friend class Collider;

	std::shared_ptr<Neoguri> GetNeoguri();
	std::shared_ptr<Map> GetMap();
	/*std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();*/

	const POINT& GetNGRPosition() const { return _posNGR; }
	void SetNGRPosition(const POINT& p);
	void SetMapNum(int num);//맵이 업데이트때 실행
	// Scene이 호출하는 부분
	void Init();
	void Update();	// 돌아가면서 Update
	virtual void Draw();	// 각 부분을 Draw 차례를 설정
	// 이벤트를 받았을때
	virtual void OnNotifyEvent(Subject* sub, int evt);
	void RemovePrey(EventPreyRemove* evnt);
};

class LoggedPartsMgr : public PartsMgr
{
public:
	LoggedPartsMgr(InGame* in) : PartsMgr(in) {}
	inline virtual void AddMonster(int numOfFloorOn, int srtX, int endX, int dir) override {
		Log("몬스터 생성");
		PartsMgr::AddMonster(numOfFloorOn, srtX, endX, dir);
	}
	virtual void Draw() override;
	

private:
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 255));
	TimeMgr* timer = TimeMgr::GetInstance();
	inline void Log(const char* message) {
		std::cout << message << std::endl;
	}
};