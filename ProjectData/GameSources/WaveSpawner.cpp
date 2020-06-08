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
		m_defaultObjectNum = { 3, 5, 2 };
		m_spawnCount = 0;
		m_offScreen = 12.0f;

		m_waveState.Pos = { Vec3(6.0f, -3.0f, -7.0f),Vec3(6.0f, -2.5f, -7.0f),Vec3(6.0f, -2.3f, -7.0f) };
		m_waveState.Rot = Vec3(0.0f);
		m_waveState.Sca = { Vec3(1.0f), Vec3(1.8f), Vec3(2.2f, 1.6f, 1.0f)};
		m_waveState.Layer = 6;
		m_waveState.Tex = { L"SamllWave.png", L"MediumWave.png", L"BigWave1.png" };

		m_createBigWaveTimer = 0.0f;
		m_maxWaitingTime = 2.0f;
	}

	void WaveSpawner::OnCreate() {
		LoadCSV(en_ObjectType::en_Wave);
		CreateObject();
	}

	void WaveSpawner::OnUpdate() {
		CreateBigWave();
		SpawnObject();
	}

	//プールするオブジェクトの作成
	void WaveSpawner::CreateObject() {
		for (int i = 0; i < 3; i++) {
			m_waveObject.push_back(vector<shared_ptr<Wave>>());
			WaveType waveType;

			switch (i)
			{
			case 0:
				waveType = WaveType::en_waveS;
				break;
			case 1:
				waveType = WaveType::en_waveM;
				break;
			case 2:
				waveType = WaveType::en_waveL;
				break;
			default:
				waveType = WaveType::en_waveL;
				break;
			}

			for (int j = 0; j < m_defaultObjectNum[i]; j++) {
				Vec3 firstPos = Vec3(-6.0f, m_waveState.Pos[i].y, m_waveState.Pos[i].z);
				m_waveObject[i].push_back(GetStage()->AddGameObject<Wave>(m_waveState.Rot, m_waveState.Sca[i], firstPos, m_waveState.Layer, m_waveState.Tex[i], waveType));
			}
		}
	}

	void WaveSpawner::SpawnObject() {
		if (!GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			float gameSpeed = GameManager::GetInstance().GetGameSpeed();

			m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

			//次に生成する波の座標を取っている
			float spawnTime = m_createPosX[m_spawnCount] - m_offScreen;

			//今の距離と次に生成する座標
			if (m_spawnTimer >= spawnTime) {
				int waveTypeNum = m_waveTypeNum[m_spawnCount];
				VisibleObject(waveTypeNum);
			}
			EndCreateObject();
		}
	}

	void WaveSpawner::VisibleObject(int waveTypeNum) {
		if (m_spawnCount > (int)m_createPosX.size() - 1) {
			return;
		}

		for (int i = 0; i < m_waveObject[waveTypeNum].size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_waveObject[waveTypeNum][i]->GetIsMove()) {
				m_waveObject[waveTypeNum][i]->GetComponent<Transform>()->SetPosition(m_waveState.Pos[waveTypeNum]);
				m_waveObject[waveTypeNum][i]->SetIsMove(true);
				if (waveTypeNum != WaveType::en_waveL) {
					m_spawnCount++;
				}
				break;
			}

			//動かせるものがなかったら作成する
			if (m_waveObject.size() - 1 == i) {
				WaveType waveType = waveTypeNum == 0 ? WaveType::en_waveS : WaveType::en_waveM;
				m_waveObject[waveTypeNum].push_back(GetStage()->AddGameObject<Wave>(m_waveState.Rot, m_waveState.Sca[waveTypeNum], m_waveState.Pos[waveTypeNum], m_waveState.Layer, m_waveState.Tex[waveTypeNum], waveType));
				m_waveObject[waveTypeNum][m_waveObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	void WaveSpawner::CreateBigWave() {
		auto &gameManager = GameManager::GetInstance();

		if (gameManager.GetIsSpecialTime()) {
			gameManager.SetIsStopSpawner(true);
			m_isStopSpawn = true;
			if (!m_isCreateBigWave && m_createBigWaveTimer > m_maxWaitingTime) {
				VisibleObject((int)WaveType::en_waveL);
				m_isCreateBigWave = true;
			}
			else {
				m_createBigWaveTimer += App::GetApp()->GetElapsedTime();
			}
		}
		else if (m_isCreateBigWave)
		{
			gameManager.SetIsStopSpawner(false);
			m_createBigWaveTimer = 0.0f;
			m_isStopSpawn = false;
			m_isCreateBigWave = false;
		}

		if (m_isCreateBigWave && !m_waveObject[WaveType::en_waveL][0]->GetIsMove()) {
			gameManager.SetIsSpecialTime(false);
		}
	}

	void WaveSpawner::EndCreateObject() {
		int spawnItr = (int)m_createPosX.size() - 1;
		if (m_spawnCount > spawnItr) {
			m_isStopSpawn = true;
			Bit_SpawnFlag spawnFlag;
			auto gameStage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();
			gameStage->TrueSpawnFlag(spawnFlag.wave);
		}
	}
}