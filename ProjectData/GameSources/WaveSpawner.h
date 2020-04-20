/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WaveSpawner : public SpawnerBase {
		vector<shared_ptr<Wave>> m_waveObject;

		Vec3 m_spawnPos;

		int m_defaultObjectNum;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		float m_offScreen;
		bool m_isStopSpawn;

	public:
		WaveSpawner(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		//プーリングするオブジェクトの作成
		void CreateObject();

		//オブジェクトを写す
		void VisibleObject();

		//オブジェクトを生成する
		void SpawnObject();

		void EndCreateObject();
	};
}