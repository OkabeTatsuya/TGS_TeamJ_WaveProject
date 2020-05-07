/*!
@file RandomGenerator.h
@brief ランダムな間隔で生成させるオブジェクト
*/

#pragma once
#include "stdafx.h"
#include <random>

namespace basecross {
	class RandomGenerator : public SpawnerBase {
		BackGroundState m_objState;

		vector<shared_ptr<MoveBG>> m_BGObject;
		vector<float> m_createPos;

		Vec3 m_spawnPos;

		int m_defaultObjectNum;
		int m_spawnCount;

		float m_mimNum;
		int m_maxNum;

		float m_spawnTimer;
		float m_generatPosX;
		bool m_isStopSpawn;

	public:
		//生成間隔のランダム生成
		RandomGenerator(const shared_ptr<Stage>& StagePtr, BackGroundState ObjectState, float mimNum, int maxNum);

		virtual void OnCreate();

		virtual void OnUpdate();

		void GeneratBG();

		void CreateObject();

		void VisibleBG();

		float RandomNum(float mimNum, int maxNum);

		float RandomSpeed(float mimSpeed, float maxSpeed);

		Vec3 RandomPos(float mimPosY, int maxPosY);
	};
}