/*!
@file ItemGenerator.h
@brief �Q�[�����Ǘ�����I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ItemGenerator : public SpawnerBase {
		vector<shared_ptr<ScoreUpItem>> m_itemObject;

		Vec3 m_spawnPos;
		Vec2 m_texSize;

		int m_defaultObjectNum;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		float m_offScreen;
		bool m_isStopSpawn;

	public:
		ItemGenerator(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		//�v�[�����O����I�u�W�F�N�g�̍쐬
		void CreateObject();

		//�I�u�W�F�N�g���ʂ�
		void VisibleObject();

		//�I�u�W�F�N�g�𐶐�����
		void SpawnObject();

		void EndCreateObject();
	};
}