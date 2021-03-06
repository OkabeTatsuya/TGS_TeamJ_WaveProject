/*!
@file WaveSpawner.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GoalGenerator::GoalGenerator(const shared_ptr<Stage>& StagePtr) :
		SpawnerBase(StagePtr)
	{
		m_objState1 = { Vec3(0.0f), Vec3(5.0f, 5.0f, 3.0f), Vec3(-10.0f,-0.5f,-9.0f), 9, L"Goal12ver.png" };
		m_objState2 = { Vec3(0.0f), Vec3(5.0f, 5.0f, 3.0f), Vec3(-10.0f,-0.5f,-5.0f), 5, L"Goal2ver.png" };
		m_goalObjState = { m_objState1,m_objState2 };
		m_offsetPos = 8.5f;

		m_spawnTimer = 0.0f;
		m_maxSpawnTime = 2.0f;
	}

	void GoalGenerator::OnCreate() {
		CreateObject();
	}

	void GoalGenerator::OnUpdate() {
		GeneratGoal();
	}

	void GoalGenerator::CreateObject() {
		m_goalObject.push_back(GetStage()->AddGameObject<GoalObject>(m_objState1.Rot, m_objState1.Scr, m_objState1.Pos, m_objState1.Layer, m_objState1.Tex));
		m_goalObject.push_back(GetStage()->AddGameObject<GoalObject>(m_objState2.Rot, m_objState2.Scr, m_objState2.Pos, m_objState2.Layer, m_objState2.Tex));
	}

	void GoalGenerator::GeneratGoal() {
		Bit_SpawnFlag spawnFlag;
		auto gameStage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();

		if (!m_isStopSpawn) {
			auto waveFlag = gameStage->ConfirmSpawnFlag(spawnFlag.wave);
			auto ItemFlag = gameStage->ConfirmSpawnFlag(spawnFlag.item);
			auto stopSpawner = waveFlag && (ItemFlag && true) ? true : false;

			if (stopSpawner) {
				auto delter = App::GetApp()->GetElapsedTime();
				m_spawnTimer += delter;
				//VisibleGoal();
			}

			if (m_maxSpawnTime < m_spawnTimer) {
				VisibleGoal();
			}
		}
	}

	//オブジェクトを表示する
	void GoalGenerator::VisibleGoal() {
		for (int i = 0; i < m_goalObject.size(); i++) {
			if (!m_goalObject[i]->GetIsMove()) {
				m_goalObject[i]->GetComponent<Transform>()->SetPosition(Vec3(m_offsetPos, m_goalObjState[i].Pos.y, m_goalObjState[i].Pos.z));
				m_goalObject[i]->SetIsMove(true);
			}
			else {
				m_goalObject[i]->GetComponent<Transform>()->SetPosition(Vec3(m_offsetPos, m_goalObjState[i].Pos.y, m_goalObjState[i].Pos.z));
				m_goalObject[i]->SetIsMove(true);
			}
		}
		m_isStopSpawn = true;
	}

	void GoalGenerator::EndGeneratGoal() {
		auto gameEndFlag = GameManager::GetInstance().GetIsGameEnd();

		if (gameEndFlag && !m_isStopSpawn) {
			auto delter = App::GetApp()->GetElapsedTime();
			m_spawnTimer += delter;
		}

		if (m_maxSpawnTime < m_spawnTimer) {
			m_isStopSpawn = true;
		}
	}
}