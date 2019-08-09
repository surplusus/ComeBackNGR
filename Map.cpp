#pragma region 맵 선언부
#include "stdafx.h"
#include "Map.h"
#include "Basic_Value.h"
#ifdef _DEBUG
#include "library/jsoncpp/include/json/json.h"
#else
#include "library/jsoncpp/include/json/json.h"
#pragma comment(lib,"library/jsoncpp/lib/lib_json.lib")
#endif // _RELEASE
#pragma warning(disable: 4996)
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
#pragma endregion
Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
	//stringstream ss;
	//for (int i = 1; i < T_MAPCOUNT; ++i)
	//{
	//	ss << "image/map/map" << i << ".bmp";
	//	std::cout << ss.str() << std::endl;
	//	string st3 = ss.str();
	//	size_t origsize = st3.length() + 1;
	//	size_t convertedChars = 0;
	//	wchar_t wcstring[30];
	//	mbstowcs_s(&convertedChars, wcstring, origsize, st3.c_str(), _TRUNCATE);
	//	_maplist[i-1] = (HBITMAP)LoadImage(NULL,wcstring,IMAGE_BITMAP
	//		,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//	ss.str("");
	//}
	ReadJSONConfigFile(_curMapNum);
	_hdc = CreateCompatibleDC(g_hmemdc);
	// EventBus
	EventBus::GetInstance()->Subscribe(this, &Map::GoToNextMap);
}

void Map::Update()
{
	for (auto &L : _ladder)
		if (PtInRect(&L, _partsManager->GetNGRPosition()))
			Notify(LADDER);
	for (auto &C : _cliff)
		if (PtInRect(&C, _partsManager->GetNGRPosition()))
			Notify(DIE);
}

void Map::Draw()
{
	if (_maplist == NULL)
	{
		std::cout << "맵 HBITMAP이 NULL 입니다." << std::endl;
		exit(0);
	}
	SelectObject(_hdc, _maplist);
	BitBlt(g_hmemdc, 0, 0, WindowWidth, WindowHeight, _hdc, 0, 0, SRCCOPY);
#ifdef _DEBUG
	static bool flag = false;
	if (!flag)	{
		std::cout << "맵 그리기" << std::endl;
		flag = true;
	}
#endif // _DEBUG
}

void Map::SelectMapNum(int num)
{
	_curMapNum = num;
}

void Map::GoToNextMap(EventCheatOperator* cheat)
{
	_ladder.clear();
	_cliff.clear();
	_curMapNum++;
	_partsManager->SetMapNum(_curMapNum);
}

void Map::ReadJSONConfigFile(int numMap)
{
	stringstream sst;
	string str;
	// JSON 파싱 준비
	sst << "image/map/map" << numMap << ".json";
	ifstream ist(sst.str());		sst.str("");
	for (char p; ist >> p;)
		str += p;
	Json::Reader reader;
	Json::Value root;
	bool parsingRet = reader.parse(str, root);
	// 맵 배경 이미지 백터 생성
	size_t origsize = root["MapImageName"].asString().length() + 1;
	size_t convertedChars = 0;		wchar_t wcstring[30];
	mbstowcs_s(&convertedChars, wcstring, origsize, root["MapImageName"].asCString(), _TRUNCATE);
	_maplist = (HBITMAP)LoadImage(NULL, wcstring, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	// Ladder 만들기
	Json::Value lad = root["Ladder"];
	for (auto &it : lad)
	{
		RECT re;
		re.left = it[0].asInt();
		re.top = it[1].asInt();
		re.right = it[2].asInt();
		re.bottom = it[3].asInt();
		_ladder.push_back(re);
	}
	// Cliff 만들기
	Json::Value cli = root["Cliff"];
	for (auto &it : cli)
	{
		RECT re;
		re.left = it[0].asInt();
		re.top = it[1].asInt();
		re.right = it[2].asInt();
		re.bottom = it[3].asInt();
		_cliff.push_back(re);
	}
}