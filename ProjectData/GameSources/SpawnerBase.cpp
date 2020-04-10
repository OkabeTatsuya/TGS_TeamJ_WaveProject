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
		m_defaultObjectNum = 5;
		m_spawnCount = 0;
		m_spawnPos = Vec3(6.0f, -3.2, -4.0f);
	}

	SpawnerBase::~SpawnerBase() {

	}

	void SpawnerBase::LoadCSV() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);
		int itr = 2;
		auto csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.stageStr[itr] + L".csv";
		//auto csvFilePths = mediaDir + L"CSV/" + L"Stage1.csv";
		CsvFile LoadCsvFile;
		m_gameStageCs.SetFileName(csvFilePths);
		m_gameStageCs.ReadCsv();

		auto& lineVec = m_gameStageCs.GetCsvVec();
		for (size_t i = 0; i < lineVec.size(); i++) {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, lineVec[i], L',');
			for (size_t j = 0; j < tokens.size(); j++) {
				float num = stof(tokens[j]);
				m_createPos.push_back(num);
			}
		};
	}

	void SpawnerBase::LoadCreatePostion() {
	}

	//プールするオブジェクトの作成
	void SpawnerBase::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			Vec3 firstPos = Vec3(-6.0f, m_spawnPos.y, m_spawnPos.z);
			m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), firstPos));
		}
	}

	void SpawnerBase::SpawnObject() {
		if (!GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			float gameSpeed = GameManager::GetInstance().GetGameSpeed();

			m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

			float spawnTime = m_createPos[m_spawnCount] / gameSpeed;

			if (spawnTime <= m_spawnTimer) {
				VisibleObject();
			}
			EndCreateObject();
		}
	}

	void SpawnerBase::VisibleObject() {
		for (int i = 0; i < m_waveObject.size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_waveObject[i]->GetIsMove()) {
				m_waveObject[i]->GetComponent<Transform>()->SetPosition(m_spawnPos);
				m_waveObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//動かせるものがなかったら作成する
			if (m_waveObject.size()-1 == i) {
				m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), m_spawnPos));
				m_waveObject[m_waveObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	void SpawnerBase::EndCreateObject() {
		int spawnItr = (int)m_createPos.size() - 1;
		if (m_spawnCount > spawnItr) {
			m_isStopSpawn = true;
			GameManager::GetInstance().SetIsStopSpawner(true);
			//m_spawnCount = 0;
			//m_spawnTimer = 0.0f;
		}
	}


}