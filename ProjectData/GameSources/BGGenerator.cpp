/*!
@file WaveSpawner.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BGGenerator::BGGenerator(const shared_ptr<Stage>& StagePtr,ObjectState ObjectState) :
		SpawnerBase(StagePtr)
	{
		//m_objState = { Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(-1280.0f,0.0f), 6.0f, L"BGImage.png" };
		m_objState = ObjectState;
		m_defaultObjectNum = 1;
	}

	void BGGenerator::OnCreate() {
		CreateObject();
	}

	void BGGenerator::OnUpdate() {
		GeneratBG();
	}

	void BGGenerator::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			//m_moveObject.push_back(m_moveObjectTile[0]);
			m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Scr, m_objState.Pos, m_objState.Tex, m_objState.OffScreenX));
		}
		m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Scr, Vec3(0.0f, m_objState.Pos.y, m_objState.Pos.z), m_objState.Tex, m_objState.OffScreenX));
		m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Scr, Vec3(10.0f, m_objState.Pos.y, m_objState.Pos.z), m_objState.Tex, m_objState.OffScreenX));
	}


	void BGGenerator::GeneratBG() {
		float gameSpeed = GameManager::GetInstance().GetGameSpeed();

		m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

		if (10.0f <= m_spawnTimer) {
			VisibleBG();
			m_spawnTimer = 0.0f;
		}			
	}

	void BGGenerator::VisibleBG() {
		for (int i = 0; i < m_BGObject.size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_BGObject[i]->GetIsMove()) {
				m_BGObject[i]->GetComponent<Transform>()->SetPosition(Vec3(10.0f, m_objState.Pos.y, m_objState.Pos.z));
				m_BGObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//動かせるものがなかったら作成する
			if (m_BGObject.size() - 1 == i) {
				m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Scr, m_objState.Pos, m_objState.Tex, m_objState.OffScreenX));
				m_BGObject[m_BGObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	void BGGenerator::EndGeneratBG() {
		auto gameEndFlag = GameManager::GetInstance().GetIsGameEnd();
		if (gameEndFlag)
			m_isStopSpawn = true;
	}
}