/*!
@file WaveSpawner.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	WaveSpawner::WaveSpawner(const shared_ptr<Stage>& StagePtr) : 
		SpawnerBase(StagePtr)
	{
		m_defaultObjectNum = 10;
		m_spawnCount = 0;
		m_offScreen = 10.0f;
		m_spawnPos = Vec3(6.0f, -3.2f, -4.0f);
	}

	void WaveSpawner::OnCreate() {
		LoadCSV();
		CreateObject();
	}

	void WaveSpawner::OnUpdate() {
		SpawnObject();
	}

	//プールするオブジェクトの作成
	void WaveSpawner::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			Vec3 firstPos = Vec3(-6.0f, m_spawnPos.y, m_spawnPos.z);
			m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), firstPos));
		}
	}

	void WaveSpawner::SpawnObject() {
		if (!GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			float gameSpeed = GameManager::GetInstance().GetGameSpeed();

			//時間に速さをかけているので距離になるはず
			m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

			//次に生成する波の座標を取っている
			float spawnTime = m_createPos[m_spawnCount] - m_offScreen;

			//今の距離と次に生成する座標
			if (m_spawnTimer >= spawnTime) {
				VisibleObject();
			}
			EndCreateObject();
		}
	}

	void WaveSpawner::VisibleObject() {
		for (int i = 0; i < m_waveObject.size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_waveObject[i]->GetIsMove()) {
				m_waveObject[i]->GetComponent<Transform>()->SetPosition(m_spawnPos);
				m_waveObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//動かせるものがなかったら作成する
			if (m_waveObject.size() - 1 == i) {
				m_waveObject.push_back(GetStage()->AddGameObject<Wave>(Vec3(0.0f), Vec3(1.0f), m_spawnPos));
				m_waveObject[m_waveObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	void WaveSpawner::EndCreateObject() {
		int spawnItr = (int)m_createPos.size() - 1;
		if (m_spawnCount > spawnItr) {
			m_isStopSpawn = true;
			Bit_SpawnFlag spawnFlag;
			auto gameStage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();
			gameStage->TrueSpawnFlag(spawnFlag.item);
			gameStage->TrueSpawnFlag(spawnFlag.wave);
		}
	}
}