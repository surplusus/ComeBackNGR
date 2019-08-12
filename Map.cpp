#pragma region �� �����
#include "stdafx.h"
#include "Map.h"
#include "library/rapidjson/include/document.h" // rapidjson ������
#include "library/rapidjson/include/prettywriter.h" // stringify JSON
#include "library/rapidjson//include/istreamwrapper.h"//ifstream ���� JSON�θ��� ���
#include "library//rapidjson//include/filereadstream.h"// CŸ���� FILE ����ü�� JSON�Ľ� ���
#include "Basic_Value.h"

#pragma endregion

Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
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
		std::cout << "�� HBITMAP�� NULL �Դϴ�." << std::endl;
		exit(0);
	}
	SelectObject(_hdc, _maplist);
	BitBlt(g_hmemdc, 0, 0, WindowWidth, WindowHeight, _hdc, 0, 0, SRCCOPY);
#ifdef _DEBUG
	static bool flag = false;
	if (!flag)	{
		std::cout << "�� �׸���" << std::endl;
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
	using namespace rapidjson;
	//wchar_t fstr;
	//_tcprintf(&fstr, "%s", sst.str().c_str());
	//FILE* fp;
	//errno_t err = ::_tfopen_s(&fp, &fstr, _T("rb"));
	//if (err)
	//{
	//	std::cerr << "not open file" << endl;
	//	return;
	//}
	/*if (!ifs.is_open())
	{
		std::cerr << "not open file" << endl;
		return;
	}*/

#pragma region C��� style file �Է� JSON
	/*FILE* fp;
	errno_t err = fopen_s(&fp, "image/map/map1.json", "rb");
	if (err) {
		std::cerr << "cannot open file" << endl;
		exit(0); }
	char fileBuffer[65536];
	FileReadStream is(fp,fileBuffer,sizeof(fileBuffer));
	Document doc;
	doc.ParseStream(is);
	fclose(fp);
	*/
#pragma endregion
#pragma region C++ ��� style filestream �Է� JSON
	stringstream sst;
	sst << "image/map/map" << numMap << ".json";
	ifstream ifs(sst.str().c_str());	sst.str("");
	IStreamWrapper isw(ifs);
	Document doc;
	doc.ParseStream(isw);
#pragma endregion
	try
	{
		assert(doc.IsObject());
		assert(doc.HasMember("MapImageName"));
		//�� ��� �̹��� ���� ����
		size_t origsize = doc["MapImageName"].GetStringLength() + 1;
		size_t convertedChars = 0;		wchar_t wcstring[30];
		mbstowcs_s(&convertedChars, wcstring, origsize, doc["MapImageName"].GetString(), _TRUNCATE);
		_maplist = (HBITMAP)LoadImage(NULL, wcstring, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		// Ladder �����
		const Value& lad = doc["Ladder"];
		auto it_lad = lad.MemberBegin();
		for (; it_lad != lad.MemberEnd(); ++it_lad)
		{
			RECT re;
			re.left		= it_lad->value[0].GetInt();
			re.top		= it_lad->value[1].GetInt();
			re.right	= it_lad->value[2].GetInt();
			re.bottom	= it_lad->value[3].GetInt();
			_ladder.push_back(re);
		}
		// Cliff �����
		const Value& cli = doc["Ladder"];
		auto it_cli = lad.MemberBegin();
		for (; it_cli != lad.MemberEnd(); ++it_cli)
		{
			RECT re;
			re.left		= it_cli->value[0].GetInt();
			re.top		= it_cli->value[1].GetInt();
			re.right	= it_cli->value[2].GetInt();
			re.bottom	= it_cli->value[3].GetInt();
			_cliff.push_back(re);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
		exit(0);
	}
	
}