/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
        //ジャンプのフラグ
        bool m_isJump = true;
        //空中アクションのフラグ
        bool m_isJumpAction = false;
        //回転固定用のVec3
        Vec3 m_initRotation;
        //Y座標以外の固定用Vec３
        Vec3 m_initPosition;
        //高いジャンプの上昇量
        float m_highJumpMoveY = 8;
        //低いジャンプの上昇量
        float m_lowJumpMoveY = 5;
        //移動速度上限
        float m_maxSpeed = 5;
        //移動速度加減
        float m_minSpeed = 2;
        //現在の移動速度
        float m_currentSpeed = (m_maxSpeed-m_minSpeed)/3+m_minSpeed;
    public:
        Player(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnUpdate2()override;
        //コリジョンの最初に当たった瞬間１回のみの処理
        virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
        //コリジョンに当たり続けているときの処理
        virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;
        //コリジョンから抜けた瞬間１回のみの処理
        virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;
        //ジャンプ
        void Jump();
        //高いジャンプ
        void HighJump();
        //低いジャンプ
        void LowJump();
        //初期化
        void Initialize();
        //現在の移動速度のゲッター
        float GetCurrentSpeed() {
            return m_currentSpeed;
        }
    };

}
//end basecross

