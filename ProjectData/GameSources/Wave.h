/*!
@file Character.h
@brief 動いてくる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Wave : public ObjectBase {
    protected:
        //移動速度
        float m_moveSpeed;
        //動いているかどうか
        bool m_isMove;
        //画面外判定のｘ座標
        float m_offScreenX;
    public:
        Wave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;

        void Move();
        bool GetIsMove();
        void SetIsMove(bool move);
        //画面外に出たかどうかの判定
        void OffScreen();
    };
}
//end basecross
