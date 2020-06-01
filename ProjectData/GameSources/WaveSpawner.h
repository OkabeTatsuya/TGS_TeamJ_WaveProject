/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum WaveType {
		en_waveS,
		en_waveM,
		en_waveL
	};

	struct WaveState
	{
		Vec3 Rot;
		vector<Vec3> Sca;
		vector<Vec3> Pos;
		int Layer;
		vector<wstring> Tex;
	};

	class WaveSpawner : public SpawnerBase {
		WaveState m_waveState;

		//波を保存
		//[波の種類][波の個数]
		vector<vector<shared_ptr<Wave>>>m_waveObject;

		//事前に生成するオブジェクトの個数
		vector<int> m_defaultObjectNum;
		//生成したオブジェクトの個数
		int m_spawnCount;
		//オブジェクトの生成する時間
		float m_spawnTimer = 0.0f;
		//画面外のX座標
		float m_offScreen;
		//スポナーを止めるフラグ
		bool m_isStopSpawn;
		//ビッグウェーブ生成用のタイマー
		float m_createBigWaveTimer;
		//ビッグウェーブを生成する時間
		float m_maxWaitingTime;
		//ビッグウエーブが生成されたフラグ
		bool m_isCreateBigWave;

	public:
		WaveSpawner(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();

		float GetSpawnTimer() { return m_spawnTimer; }
		float GetMaxCreatePosX() { return m_createPosX.back(); }

		//プーリングするオブジェクトの作成
		void CreateObject();

		//オブジェクトを写す
		void VisibleObject(int waveTypeNum);

		//オブジェクトを生成する
		void SpawnObject();

		//スペシャルタイムの波を生成する
		void CreateBigWave();

		void EndCreateObject();
	};
}