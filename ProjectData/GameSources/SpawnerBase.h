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
		};

	};
	class SpawnerBase : public GameObject {
		FileNameCSV m_strFileNameCSV;
		CsvFile m_gameStageCs;

		vector<CsvFile> m_gameStageCsv;
		vector<shared_ptr<Wave>> m_waveObject;
		vector<float> m_createPos;

		Vec3 m_spawnPos;

		int m_defaultObjectNum;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		bool m_isStopSpawn;

	public:
		SpawnerBase(const shared_ptr<Stage>& StagePtr);

		~SpawnerBase();

		void LoadCSV();

		//CSVからポジションデータを取ってくる
		void LoadCreatePostion();

		//プーリングするオブジェクトの作成
		void CreateObject();

		//オブジェクトを写す
		void VisibleObject();

		//オブジェクトを生成する
		void SpawnObject();

		//オブジェクト生成を止める
		void EndCreateObject();

	};
}