/*!
@file WaveSpawner.cpp
@brief ゲームオブジェクト生成クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	WaveSpawner::WaveSpawner(const shared_ptr<Stage>& StagePtr) : 
		SpawnerBase(StagePtr)
	{
	}

	void WaveSpawner::OnCreate() {
		LoadCSV();
		CreateObject();
		//LoadCreatePostion();
	}

	void WaveSpawner::OnUpdate() {
		SpawnObject();
	}
}