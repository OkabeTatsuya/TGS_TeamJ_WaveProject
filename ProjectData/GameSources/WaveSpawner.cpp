/*!
@file WaveSpawner.cpp
@brief �Q�[���I�u�W�F�N�g�����N���X�̎���
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