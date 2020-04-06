/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GoalGenerator : public SpawnerBase {
		ObjectState m_objState;
		
		shared_ptr<GoalObject> m_goalObject;
		vector<float> m_createPos;

		Vec3 m_spawnPos;

		float m_offsetPos;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		bool m_isStopSpawn;

	public:
		GoalGenerator(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		void GeneratGoal();

		void CreateObject();

		void VisibleGoal();

		void EndGeneratGoal();

	};
}