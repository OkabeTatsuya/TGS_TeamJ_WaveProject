/*!
@file ItemGenerator.cpp
@brief �Q�[���I�u�W�F�N�g�����N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ItemGenerator::ItemGenerator(const shared_ptr<Stage>& StagePtr) : 
		SpawnerBase(StagePtr)
	{
		m_defaultObjectNum = 10;
		m_spawnCount = 0;
		m_offScreen = 10.0f;
		m_spawnPos = Vec3(6.0f, -3.2f, -6.0f);
		m_texSize = Vec2(1.0f);
	}

	void ItemGenerator::OnCreate() {
		LoadCSV(en_ObjectType::en_Item);
		CreateObject();
	}

	void ItemGenerator::OnUpdate() {
		SpawnObject();
	}

	//�v�[������I�u�W�F�N�g�̍쐬
	void ItemGenerator::CreateObject() {
		for (int i = 0; i < m_defaultObjectNum; i++) {
			Vec3 firstPos = Vec3(-6.0f, m_spawnPos.y, m_spawnPos.z);
			m_itemObject.push_back(GetStage()->AddGameObject<ScoreUpItem>(Vec3(0.0f) , firstPos, m_texSize));
		}
	}

	void ItemGenerator::SpawnObject() {
		if (!GameManager::GetInstance().GetIsStopSpawner() && !m_isStopSpawn) {
			float gameSpeed = GameManager::GetInstance().GetGameSpeed();

			//���Ԃɑ����������Ă���̂ŋ����ɂȂ�͂�
			m_spawnTimer += App::GetApp()->GetElapsedTime() * gameSpeed;

			//���ɐ�������A�C�e���̍��W������Ă���
			float spawnTime = m_createPosX[m_spawnCount] - m_offScreen;

			//���̋����Ǝ��ɐ���������W
			if (m_spawnTimer >= spawnTime) {
				VisibleObject();
			}
			EndCreateObject();
		}
	}

	void ItemGenerator::VisibleObject() {
		for (int i = 0; i < m_itemObject.size(); i++) {
			//�v�[�����O�����I�u�W�F�N�g���瓮��������̂�T��
			if (!m_itemObject[i]->GetIsMove()) {
				m_itemObject[i]->GetComponent<Transform>()->SetPosition(Vec3(6.0f, m_createPosY[m_spawnCount], -6.0f));
				m_itemObject[i]->SetIsMove(true);
				m_spawnCount++;
				break;
			}

			//����������̂��Ȃ�������쐬����
			if (m_itemObject.size() - 1 == i) {
				m_itemObject.push_back(GetStage()->AddGameObject<ScoreUpItem>(Vec3(0.0f), Vec3(6.0f, m_createPosY[m_spawnCount], -6.0f), m_texSize));
				m_itemObject[m_itemObject.size() - 1]->SetIsMove(true);
				m_spawnCount++;
				break;
			}
		}
	}

	void ItemGenerator::EndCreateObject() {
		int spawnItr = (int)m_createPosX.size() - 1;
		if (m_spawnCount > spawnItr) {
			m_isStopSpawn = true;
			Bit_SpawnFlag spawnFlag;
			auto gameStage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();
			gameStage->TrueSpawnFlag(spawnFlag.item);
		}
	}
}