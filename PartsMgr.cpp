#pragma region using ����
#include "stdafx.h"
#include "InGame.h"
#include "InGamePart.h"
#include "Map.h"
#include "Prey.h"
#include "Monster.h"
#include "Obstacle.h"
#include "Neoguri.h"
#include "Observer.h"
#include "Basic_Value.h"
#ifdef _DEBUG
#include "library/jsoncpp/include/json/json.h"
#else
#include "library/jsoncpp/include/json/json.h"
#pragma comment(lib,"library/jsoncpp/lib/lib_json.lib")
#endif // _RELEASE
#pragma warning(disable: 4996)
using std::make_pair;
using std::type_index;
using std::pair;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::static_pointer_cast;
#pragma endregion
PartsMgr::PartsMgr(InGame *ingame)
{
	_callerAsScene = ingame;
}
PartsMgr::~PartsMgr()
{
	_parts.clear();
}

#pragma region Getters
shared_ptr<Neoguri> PartsMgr::GetNeoguri()
{
	return static_pointer_cast<Neoguri>(_parts["Neoguri1"]);
}

shared_ptr<Map> PartsMgr::GetMap()
{
	stringstream ss("Map");
	ss << numOfCurrentMap;
	return static_pointer_cast<Map>(_parts[ss.str()]);
}

//vector<Monster*> PartsMgr::GetMonsters()
//{
//	stringstream ss;
//	vector<Monster*> mon;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Monster" << i;
//		auto it = _parts.find(ss.str());
//		if (_parts.find(ss.str()) != _parts.end())
//			if (it->second != nullptr)
//				mon.push_back(static_cast<Monster*>(_parts.find(ss.str())->second));
//	}
//
//	return mon;
//}
//
//vector<Prey*> PartsMgr::GetPreys()
//{
//	stringstream ss;
//	vector<Prey*> prey;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Prey" << i;
//		auto it = _parts.find(ss.str());
//		if (it != _parts.end()) {
//			if (it->second != nullptr)
//				prey.push_back(static_cast<Prey*>(_parts.find(ss.str())->second));
//		}
//	}
//	return prey;
//}
//
//vector<Obstacle*> PartsMgr::GetObstacle()
//{
//	stringstream ss;
//	vector<Obstacle*> obs;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Obstacle" << i;
//		auto it = _parts.find(ss.str());
//		if (_parts.find(ss.str()) != _parts.end())
//			if (it->second != nullptr)
//				obs.push_back(static_cast<Obstacle*>(_parts.find(ss.str())->second));
//	}
//	return obs;
//}
#pragma endregion Getters

#pragma region Adders
void PartsMgr::AddMonster(int numOfFloorOn, int srtX, int endX, int dir)
	// dir(����) : move left// dir(���) : move right// flr : floor
{
	string st = MakePartIndexName('m');
	// �����! firstfloor, secondfloor
	shared_ptr<InGamePart> mon = make_shared<Monster>(this,st, numOfFloorOn, srtX, endX, dir);
	//static_cast<Monster*>(mon)->SetPatrolCoordinate(srtX, endX);
	_parts[st] = mon;
}

void PartsMgr::AddObstacle(int numOfFloorOn, int coordX)
{
	shared_ptr<InGamePart> obs = make_shared<Obstacle>(this, numOfFloorOn, coordX);
	string st = MakePartIndexName('O');
	_parts[st] = obs;
}

void PartsMgr::AddPrey(int numOfFloorOn, int coordX)
{
	cntPrey = Prey::PreyMemberPtr.size();
	string st = MakePartIndexName('P');
	shared_ptr<InGamePart> prey = make_shared<Prey>(this,st, numOfFloorOn,coordX, cntPrey);

	_parts[st] = prey;
}
void PartsMgr::AddMap(int num)
{
	string st = MakePartIndexName('B', num);
	shared_ptr<InGamePart> map = make_shared<Map>(this);
	_parts[st] = map;
}
#pragma endregion Adders

std::string PartsMgr::MakePartIndexName(const char name, int num)
{
	stringstream ss;
	switch (name)
	{
	case	'p':
	case	'P':
		ss << "Prey";
		if (num == -1)		ss << ++cntPrey;
		else				ss << num;
		break;
	case	'm':
	case	'M':
		ss << "Monster";
		if (num == -1)		ss << ++cntMon;
		else				ss << num;
		break;
	case	'o':
	case	'O':
		ss << "Obstacle";
		if (num == -1)		ss << ++cntObs;
		else				ss << num;
		break;
	case	'B':
	case	'b':
		ss << "Map";
		if (num == -1)		ss << ++cntObs;
		else				ss << num;
		break;
	}

	return ss.str();
}

void PartsMgr::MakeDrawOrder()
{
	if (isDrawOrderDirty)
	{
		_partsOrderList.clear();
		stringstream ss;
		//// ���� ���� �׸���(B : background)
		ss << MakePartIndexName('B', numOfCurrentMap);
		_partsOrderList.push_back(_parts[ss.str()]);
		ss.str("");
		//// ��ֹ� �׸���(O : Obstacle)
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('O', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		//// �ʱ��� �׸���
		ss << "Neoguri1";
		_partsOrderList.push_back(_parts[ss.str()]);
		ss.str("");
		//// ���� �׸���
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('P', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		//// ���� �׸���
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('M', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		isDrawOrderDirty = false;
	}
}

void PartsMgr::MakeMonAndPreyByJSON()
{
	stringstream sst;
	string str;
	// JSON �Ľ� �غ�
	sst << "image/map/map" << numOfCurrentMap << ".json";
	std::ifstream ist(sst.str());		sst.str("");
	for (char p; ist >> p;)
		str += p;
	Json::Reader reader;
	Json::Value root;
	bool parsingRet = reader.parse(str, root);
	// Monster �����
	Json::Value mon = root["Monster"];
	for (size_t i = 1; i <= mon.size(); i++)
	{
		sst << i;
		int val[4];
		for (size_t j = 0; j < 4; ++j)
		{
			val[j] = mon[sst.str()][j].asInt();
		}
		AddMonster(val[0], val[1], val[2], val[3]);
		sst.str("");
	}
	// Prey �����
	Json::Value pr = root["Prey"];
	for (size_t i = 1; i <= pr.size(); i++)
	{
		sst << i;
		int val[2];
		for (size_t j = 0; j < 2; ++j)
		{
			val[j] = pr[sst.str()][j].asInt();
		}
		AddPrey(val[0], val[1]);
		sst.str("");
	}
	// Obstacle �����
	Json::Value ob = root["Obstacle"];
	for (size_t i = 1; i <= ob.size(); i++)
	{
		sst << i;
		int val[2];
		for (size_t j = 0; j < 2; ++j)
		{
			val[j] = ob[sst.str()][j].asInt();
		}
		AddObstacle(val[0], val[1]);
		sst.str("");
	}
}

void PartsMgr::SetNGRPosition(const POINT & p)
{
	_posNGR.x = p.x;	_posNGR.y = p.y + 10;
}

void PartsMgr::SetMapNum(int num)
{
	numOfCurrentMap = num;
	// ���� �ٲ�� ���� ���� ���̱�
	string m = "Monster";
	string p = "Prey";
	stringstream ss;
	auto it = _parts.begin();
	for (size_t i = 1; i <= _parts.size(); i++)
	{
		ss << m << i;
		if (it->first == ss.str())
			_parts.erase(it);
		ss.str("");	ss << p << i;
		if (it->first == ss.str())
			_parts.erase(it);
		ss.str("");
	}
}

void PartsMgr::Init()
{
	string stNeo = "Neoguri1";
#ifdef _DEBUG
	shared_ptr<InGamePart> neoguri = make_shared<LoggedNeoguri>(this);
	_parts[stNeo] = neoguri;
	cout << stNeo << " ����" << endl;
#else
	shared_ptr<InGamePart> neoguri = make_shared<Neoguri>(this);
#endif // _DEBUG
	// ���̸� �Ծ����� �̺�Ʈ ���
	EventBus::GetInstance()->Subscribe(this, &PartsMgr::RemovePrey);
	// �� �����ϱ� (firstfloor : 510, // dir(����) : move left// dir(���) : move right// flr : floor)
	// �ʱ����� �ٸ� ��ǥ�� �������ִ�.
	AddMap(1);	// 1��° �� �����
	MakeMonAndPreyByJSON();
}

void PartsMgr::Draw()
{
	MakeDrawOrder();
	for (auto &parts : _partsOrderList)
		parts->Draw();
}

void PartsMgr::Update()
{
	_posNGR = static_pointer_cast<Neoguri>(_parts["Neoguri1"])->GetPointNGR();

	if (isDrawOrderDirty)
	{
		MakeDrawOrder();
	}
	for (auto& part : _partsOrderList)
		part->Update();
}

void PartsMgr::OnNotifyEvent(Subject * sub, int evetType)
{
	switch (evetType)
	{
		case EVENTTYPE::NONE:
			break;
		case EVENTTYPE::DIE:
			cout << "����ֱ�" << endl;
			numOfCurrentMap++;
			AddMap(numOfCurrentMap);
			GetNeoguri()->Restart();
			_callerAsScene->IsGameOverOn();
			break;
		case EVENTTYPE::MONSTER:
			GetNeoguri()->Die();
			break;
		case EVENTTYPE::OBSTACLE:
			GetNeoguri()->Die();
			break;
		case EVENTTYPE::NOPRAYLEFT:
			numOfCurrentMap++;
			AddMap(numOfCurrentMap);
			GetNeoguri()->Restart();
			break;
		case EVENTTYPE::AIRTIME:
			cout << "Jumping" << endl;
			break;
		case EVENTTYPE::LAND:
			cout << "Land : " << endl;
			break;
		case EVENTTYPE::LADDER:
			cout << "Ladder " << endl;
			GetNeoguri()->ToggleLadderState();
			break;
		case EVENTTYPE::NEXTSTAGE:
			cout << "go to next stage" << endl;
			break;
	}
}

void PartsMgr::RemovePrey(EventPreyRemove * evnt)
{
	/*auto it = std::find(_partsOrderList.begin(), _partsOrderList.end()
		, (evnt->GetPreyPtr()));*/
	for (auto jt = _parts.begin(); jt != _parts.end(); jt++)
	{
		std::string st = jt->first;
		std::shared_ptr<InGamePart> pt = jt->second;
		if (evnt->GetPreyPtr() == static_pointer_cast<Prey>(pt))
		{
			_parts.erase(jt);
			break;
		}
	}
	//_partsOrderList.erase(it);
	MakeDrawOrder();
	isDrawOrderDirty = true;
}
