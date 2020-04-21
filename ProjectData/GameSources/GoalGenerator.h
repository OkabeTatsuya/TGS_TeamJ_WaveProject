/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GoalGenerator : public SpawnerBase {
		ObjectState m_objState1;
		ObjectState m_objState2;

		vector<ObjectState> m_goalObjState;

		vector<shared_ptr<GoalObject>> m_goalObject;
		vector<float> m_createPos;

		Vec3 m_spawnPos;

		float m_offsetPos;
		bool m_isStopSpawn;

		float m_spawnTimer;
		float m_maxSpawnTime;

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