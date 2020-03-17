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
        //ハイジャンプの上昇量
        float m_highJumpMoveY;
        //ロージャンプの上昇量
        float m_lowJumpMoveY;
        //移動速度上限
        float m_maxSpeed;
        //移動速度下限
        float m_minSpeed;
        //現在の移動速度
        float m_currentSpeed;
        //継続スピードダウンの減少量
        float m_groundWaveDownSpeedValue;
        //現在のジャンプのグレード判定秒数
        float m_currentJumpGradeTime;
        //ギリギリでジャンプした時のスピードの上昇量倍率
        float m_jumpGradeMagnification;
        //ジャンプグレード判定の難易度
        float m_jumpGradeTime;

        //空中アクション成否
        bool m_isJumpAction;
        //空中アクション中のスティック上下左右認識フラグ
        bool m_isTopJumpAction;
        bool m_isBottomJumpAction;
        bool m_isLeftJumpAction;
        bool m_isRightJumpAction;
        //空中アクションの入力時間
        float m_jumpActionLimitTime;
        //現在の空中アクションの入力にかかっている時間
        float m_currentJumpActionTime;
        //ジャンプしたときのスピードの上昇量
        float m_upSpeedValue;
        //ジャンプミスしたときのスピードの減少量
        float m_jumpMissDownSpeedValue;
    private:
        Vec3 m_rot;
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
        //ハイジャンプ
        void HighJump();
        //ロージャンプ
        void LowJump();
        //ジャンプアクション
        void JumpAction();
        //ジャンプアクションの入力判定
        void JudgeJumpAction();
        //スピードの上限下限処理
        void AdjustSpeed();
        //スピードアップ処理
        void SpeedUp(float upSpeedValue);
        //ジャンプミスのスピードダウン処理
        void JumpMissSpeedDown();
        //継続スピードダウン処理
        void GroundWaveSpeedDown();
        //現在の移動速度のゲッター
        float GetCurrentSpeed() {
            return m_currentSpeed;
        }
    };

}
//end basecross

