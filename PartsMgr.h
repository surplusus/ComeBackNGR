#pragma once
#pragma region Ŭ���� ����κ�
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
	// part ���� �����ߵ�����
	// InGamePart�� ���� Ÿ���� key�� ���� ��Ƽ���� �Ẹ�Ҵ�
	// Draw()�� ���ؼ� ��ϵǾ��ִ� key���� vector�� ������ �ִ�
	std::unordered_map<std::string, std::shared_ptr<InGamePart>> _parts;
	std::list<std::shared_ptr<InGamePart>> _partsOrderList;
	bool isDrawOrderDirty = true;
	// �ʱ����� ������ǥ
	POINT _posNGR;
	// mon, ob, rey ����
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
	void SetMapNum(int num);//���� ������Ʈ�� ����
	// Scene�� ȣ���ϴ� �κ�
	void Init();
	void Update();	// ���ư��鼭 Update
	virtual void Draw();	// �� �κ��� Draw ���ʸ� ����
	// �̺�Ʈ�� �޾�����
	virtual void OnNotifyEvent(Subject* sub, int evt);
	void RemovePrey(EventPreyRemove* evnt);
};

class LoggedPartsMgr : public PartsMgr
{
public:
	LoggedPartsMgr(InGame* in) : PartsMgr(in) {}
	inline virtual void AddMonster(int numOfFloorOn, int srtX, int endX, int dir) override {
		Log("���� ����");
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