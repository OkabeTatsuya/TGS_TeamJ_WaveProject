
/*!
@file Character.h
@brief ’n–Ê‚Æ‚È‚é”g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class GroundWave : public ObjectBase {
    protected:
        //ˆÚ“®‘¬“x
        float m_moveSpeed;
        //YÀ•W‚ÌŒÅ’è
        float m_initYPos;
    public:
        GroundWave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}
//end basecross
