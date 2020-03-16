/*!
@file WaveSpawner.h
@brief �Q�[�����Ǘ�����I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WaveSpawner : public SpawnerBase {
		
	public:
		WaveSpawner(const shared_ptr<Stage>& StagePtr);

		virtual void OnCreate();

		virtual void OnUpdate();
	};
}