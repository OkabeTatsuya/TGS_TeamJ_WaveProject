/*!
@file SpawnerBase.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpawnerBase::SpawnerBase(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{
		m_defaultObjectNum = 3;
		m_spawnCount = 0;
	}

	SpawnerBase::~SpawnerBase() {

	}

	void SpawnerBase::LoadCSV() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		int itr = 0;
		while (m_strFileNameCSV.stageStr.size() > itr) {
			auto csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.stageStr[itr] + L".csv";
			CsvFile LoadCsvFile;
			LoadCsvFile.SetFileName(csvFilePths);
			LoadCsvFile.GetCsvVec();
			//m_gameStageCsv.push_back(LoadCsvFile);
			itr++;
		}
	}

	void SpawnerBase::CreateObject() {

		while (m_spawnCount <= m_defaultObjectNum) {
			m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), Vec3(-6.0f, -1.5, 0)));
			m_spawnCount++;
		}
	}

	void SpawnerBase::SpawnObject() {
		m_spawnTimer += App::GetApp()->GetElapsedTime();

		if (m_curentTime <= m_spawnTimer) {		
			for (int i = 0; i < m_waveObject.size(); i++) {
				if (!m_waveObject[i]->GetIsMove()) {
					m_waveObject[i]->GetComponent<Transform>()->SetPosition(Vec3(6.0f, -1.5, 0));
					m_waveObject[i]->SetIsMove(true);
					break;
				}
			}
			m_spawnTimer = 0;

		}
	}
}