/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	struct ObjectState {
		Vec3 Rot;
		Vec3 Scr;
		Vec3 Pos;
		wstring Tex;
	};

	class BGGenerator : public SpawnerBase {
		ObjectState m_objState;
		
		vector<shared_ptr<MoveBG>> m_BGObject;
		vector<float> m_createPos;
		

		Vec3 m_spawnPos;

		int m_defaultObjectNum;
		int m_spawnCount;
		float m_spawnTimer = 0.0f;
		bool m_isStopSpawn;

	public:
		BGGenerator(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		void GeneratBG();

		virtual void CreateObject() override;

		void VisibleBG();

		void EndGeneratBG();
	};
}