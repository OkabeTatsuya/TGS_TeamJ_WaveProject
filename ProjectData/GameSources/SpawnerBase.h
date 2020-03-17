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
			L"Stage1",
			//L"Stage2"
		};

		vector<wstring> itemStr{
			L"Stage1Item",
			L"Stage2Item"
		};

	};
	class SpawnerBase : public GameObject {
		FileNameCSV m_strFileNameCSV;
		vector<CsvFile> m_gameStageCsv;
		vector<shared_ptr<Wave>> m_waveObject;

		int m_defaultObjectNum;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		float m_curentTime = 5.0f;
		float m_playerSpeed = 3.0f;

	public:
		SpawnerBase(const shared_ptr<Stage>& StagePtr);

		~SpawnerBase();

		void LoadCSV();

		void CreateObject();

		void SpawnObject();
	};
}