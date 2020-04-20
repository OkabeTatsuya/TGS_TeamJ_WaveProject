/*!
@file ObjectBase.h
@brief オブジェクト生成クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
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
			L"Stage1Item",
			L"Stage2Item"
			L"Stage3Item"
			L"Stage4Item"
		};

	};

	class SpawnerBase : public GameObject {
	protected:
		FileNameCSV m_strFileNameCSV;
		CsvFile m_gameStageCs;

		vector<CsvFile> m_gameStageCsv;
		vector<float> m_createPos;

	public:
		SpawnerBase(const shared_ptr<Stage>& StagePtr);

		~SpawnerBase();

		void LoadCSV();

	};
}