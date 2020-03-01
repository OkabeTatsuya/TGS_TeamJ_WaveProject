/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Enemy : public ObjectBase {

	public:
		Enemy(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position);

		virtual void OnCreate() override;
	};
}
//end basecross
