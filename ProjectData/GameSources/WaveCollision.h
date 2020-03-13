/*!
@file Character.h
@brief “®‚­”g‚Ì“–‚½‚è”»’è
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class WaveCollision : public GameObject {
    public:
        const Vec3& m_rotation;
        const Vec3& m_scale;
        const Vec3& m_position;
        float m_moveSpeed;

		WaveCollision(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position
            );

		virtual void OnCreate() override;
        virtual void OnUpdate();
	};
}
//end basecross
