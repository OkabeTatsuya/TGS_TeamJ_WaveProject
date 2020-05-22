/*!
@file ItemGenerator.h
@brief ゲームを管理するオブジェクト
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

		//プーリングするオブジェクトの作成
		void CreateObject();

		//オブジェクトを写す
		void VisibleObject();

		//オブジェクトを生成する
		void SpawnObject();

		void EndCreateObject();
	};
}