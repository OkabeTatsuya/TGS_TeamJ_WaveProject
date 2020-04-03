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
		m_objState = { Vec3(0.0f), Vec3(1.0f, 10.0f, 1.0f), Vec3(-6.0f,0.0f,-3.0f), L"BGImage.png" };
		m_offsetPos = 6.0f;
	}

	void GoalGenerator::OnCreate() {
		CreateObject();
	}

	void GoalGenerator::OnUpdate() {
		GeneratGoal();
	}

	void GoalGenerator::CreateObject() {
			m_goalObject = GetStage()->AddGameObject<GoalObject>(m_objState.Rot, m_objState.Scr, m_objState.Pos);
	}

	void GoalGenerator::GeneratGoal() {
		if (GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			VisibleGoal();			
		}
	}

	//オブジェクトを表示する
	void GoalGenerator::VisibleGoal() {
		if (!m_goalObject->GetIsMove()) {
			m_goalObject->GetComponent<Transform>()->SetPosition(Vec3(m_offsetPos, m_objState.Pos.y, m_objState.Pos.z));
			m_goalObject->SetIsMove(true);
			m_spawnCount++;
			m_isStopSpawn = true;
		}
	}

	void GoalGenerator::EndGeneratGoal() {
		auto gameEndFlag = GameManager::GetInstance().GetIsGameEnd();
		if (gameEndFlag)
			m_isStopSpawn = true;
	}
}