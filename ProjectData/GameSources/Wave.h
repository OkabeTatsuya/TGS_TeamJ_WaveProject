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
        //移動判定
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

        //移動処理
        void Move();
        //移動判定のゲッター
        bool GetIsMove();
        //移動判定のセッター
        void SetIsMove(bool move);
        //画面外判定
        void OffScreen();
    };
}
//end basecross
