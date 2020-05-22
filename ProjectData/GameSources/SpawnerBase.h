/*!
@file ObjectBase.h
@brief オブジェクト生成クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum en_ObjectType {
		en_Wave,
		en_Item
	};

	struct SpanObjectCSVPhas {
		wstring Wave = L"WaveCSV";
		wstring Item = L"ItemCSV";
		//wstring 
	};

	struct FileNameCSV {
		vector<wstring> stageStr{
			L"MapData1",
			L"MapData2",
			L"MapData3",
			L"MapData4"
		};

		vector<wstring> itemStr{
			L"ItemData1",
			L"ItemData2",
			L"ItemData3",
			L"ItemData4",
		};

	};

	class SpawnerBase : public GameObject {
	protected:
		FileNameCSV m_strFileNameCSV;
		CsvFile m_gameStageCs;

		vector<CsvFile> m_gameStageCsv;
		vector<float> m_createPosX;
		vector<float> m_createPosY;

	public:
		SpawnerBase(const shared_ptr<Stage>& StagePtr);

		~SpawnerBase();

		void LoadCSV(en_ObjectType objType);

		void ReadCSVLine(vector<wstring> csvLine, en_ObjectType objType);
	};
}