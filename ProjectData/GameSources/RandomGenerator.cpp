/*!
@file
@file RandomGenerator.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RandomGenerator::RandomGenerator(const shared_ptr<Stage>& StagePtr, BackGroundState ObjectState, float mimNum, int maxNum) :
		SpawnerBase(StagePtr)
	{
		m_objState = ObjectState;
		m_defaultObjectNum = 5;
		m_generatPosX = 10;
		m_spawnTimer = 0.0f;
		m_mimNum = mimNum;
		m_maxNum = maxNum;
	}

	void RandomGenerator::OnCreate() {
		CreateObject();
	}

	void RandomGenerator::OnUpdate() {
		GeneratBG();
	}

	void RandomGenerator::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Pos, m_objState.ImageSize, m_objState.Layer, m_objState.Tex, m_objState.OffScreenX, m_objState.MoveSpeed));
		}																						
	}

	void RandomGenerator::GeneratBG() {
		float gameSpeed = GameManager::GetInstance().GetGameSpeed();

		m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed * m_objState.MoveSpeed;

		if (RandomNum(m_mimNum,m_maxNum) <= m_spawnTimer) {
			VisibleBG();
			m_spawnTimer = 0.0f;
		}			
	}

	void RandomGenerator::VisibleBG() {
		for (int i = 0; i < m_BGObject.size(); i++) {
			//プーリングしたオブジェクトから動かせるものを探す
			if (!m_BGObject[i]->GetIsMove()) {
				m_BGObject[i]->GetComponent<Transform>()->SetPosition(m_generatPosX, m_objState.Pos.y, m_objState.Pos.z);
				m_BGObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//動かせるものがなかったら作成する
			if (m_BGObject.size() - 1 == i) {
				m_BGObject.push_back(GetStage()->AddGameObject<MoveBG>(m_objState.Rot, m_objState.Pos, m_objState.ImageSize, m_objState.Layer, m_objState.Tex, m_objState.OffScreenX, m_objState.MoveSpeed));
				m_BGObject[m_BGObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	float RandomGenerator::RandomNum(float mimNum, int maxNum) {
		std::random_device rando;
		std::mt19937 mt(rando());
		float num = mt() % (maxNum - (int)mimNum) + mimNum;

		return (float)num;
	}

	Vec3 RandomGenerator::RandomPos(float mimPosY, int maxPosY) {
		std::random_device rando;
		std::mt19937 mt(rando());
		float num = mt() % (maxPosY - (int)mimPosY) + mimPosY;

		Vec3 pos;
		bool flag = mimPosY <= 0 || maxPosY <= 0;

		if (!flag) {
			pos = Vec3(m_generatPosX, num, m_objState.Pos.z);
		}
		else {
			pos = Vec3(m_generatPosX, -num, m_objState.Pos.z);
		}

		return pos;
	}

	float RandomGenerator::RandomSpeed(float mimSpeed, float maxSpeed) {
		std::random_device rando;
		std::mt19937 mt(rando());
		int randMaxSpeed = (int)maxSpeed * 10;
		int randMimSpeed = (int)mimSpeed * 10;

		float num = (float)(mt() % (randMaxSpeed - (int)randMimSpeed) + randMimSpeed) / 10;

		return num;
	}

}