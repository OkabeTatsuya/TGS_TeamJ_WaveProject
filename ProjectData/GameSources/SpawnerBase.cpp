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
	}

	SpawnerBase::~SpawnerBase() {

	}

	void SpawnerBase::LoadCSV() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		int itr = 0;
		while (m_strFileNameCSV.stageStr.size() > itr) {
			auto csvFilePths = mediaDir + L"CSV/" + m_strFileNameCSV.stageStr[itr] + L".csv";
			//auto csvFilePths = mediaDir + L"CSV/" + L"Stage1.csv";
			CsvFile LoadCsvFile;
			m_gameStageCs.SetFileName(mediaDir + L"CSV/" + L"Stage1.csv");
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
			//m_gameStageCsv.push_back(m_gameStageCs);
			itr++;
		}
	}

	void SpawnerBase::LoadCreatePostion() {
		for (int i = 0; i < 10; i++) {
			float SetPos = 15.0f * i;
			m_createPos.push_back(SetPos);
		}
	}

	void SpawnerBase::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), Vec3(-6.0f, -1.5, 0)));
		}
	}

	void SpawnerBase::SpawnObject() {
		if (!GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			float gameSpeed = GameManager::GetInstance().GetGameSpeed();

			m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

			float move = m_createPos[m_spawnCount] * App::GetApp()->GetElapsedTime() * gameSpeed * 10.0f;

			if (move <= m_spawnTimer) {
				VisibleObject();
			}
			EndCreateObject();
		}
	}

	void SpawnerBase::VisibleObject() {
		for (int i = 0; i < m_waveObject.size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_waveObject[i]->GetIsMove()) {
				m_waveObject[i]->GetComponent<Transform>()->SetPosition(Vec3(6.0f, -1.5, 0));
				m_waveObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//動かせるものがなかったら作成する
			if (m_waveObject.size()-1 == i) {
				m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), Vec3(6.0f, -1.5, 0)));
				m_waveObject[m_waveObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}


	}

	void SpawnerBase::EndCreateObject() {
		int spawnItr = (int)m_createPos.size() - 1;
		if (m_spawnCount > spawnItr) {
			//m_isStopSpawn = true;
			m_spawnCount = 0;
			m_spawnTimer = 0.0f;
		}
	}


}