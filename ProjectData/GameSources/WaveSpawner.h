/*!
@file WaveSpawner.h
@brief ゲームを管理するオブジェクト
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