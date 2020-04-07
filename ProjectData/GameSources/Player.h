/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
        //ジャンプアクションの１回転にかかる時間
        float m_jumpActionTime;
        //ジャンプのフラグ
        bool m_isJump = true;
        //ハイジャンプの上昇量
        float m_highJumpMoveY;
        //ロージャンプの上昇量
        float m_lowJumpMoveY;
        //良ジャンプ時のジャンプの上昇量倍率
        float m_greatJumpMagnification;
        //移動速度上限
        float m_maxSpeed;
        //移動速度下限
        float m_minSpeed;
        //継続スピードダウンの減少量
        float m_groundWaveDownSpeedValue;
        //波に当たっているときの判定
        bool m_isWaveTouch;
        //現在のジャンプのグレード判定秒数
        float m_currentJumpGradeTime;
        //良ジャンプした時のスピードの上昇量倍率
        float m_jumpGradeSpeedMagnification;
        //良ジャンプしたときのスコアの上昇量倍率
        float m_jumpGradeScoreMagnification;
        //スピードに依存したスコアの倍率上限
        float m_maxSpeedScoreMagnification;
        //現在のスピードに依存したスコアの倍率
        float m_currentSpeedScoreMagnification;
        //ジャンプグレード判定時間
        float m_jumpGradeTime;
        //ジャンプグレード判定の難易度
        float m_jumpGradeTimeJudge;
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
        //ジャンプ後着地したときのスピード維持判定
        bool m_isLanding;
        //ジャンプ後着地したときのスピード維持判定上限時間
        float m_maxLandingTime;
        //現在のジャンプ後着地したときのスピード維持判定時間
        float m_currentLandingTime;
        //ジャンプミスまたは着地ミスしたときの無敵時間上限
        float m_maxInvincibleTime;
        //現在のジャンプミスまたは着地ミスしたときの無敵時間
        float m_currentInvincibleTime;
        //ジャンプミスまたは着地ミスしたときの無敵判定
        bool m_isInvincible;
        //連続で波に乗っている回数
        int m_combo;
        //１コンボで増える倍率
        float m_comboMagnification;
    private:
        //プレイヤーの角度
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
        void HighJump(float jumpMag);
        //ロージャンプ
        void LowJump(float jumpMag);
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
        //無敵時間処理
        void Invincible();
        //スピード依存のスコア倍率計算処理
        void SpeedScoreMagnification();
        //SEを鳴らす処理
        void ActiveSE(wstring se);
    };

}
//end basecross

