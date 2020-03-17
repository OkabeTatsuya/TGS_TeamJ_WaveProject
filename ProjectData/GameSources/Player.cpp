/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

    Player::Player(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {
        m_highJumpMoveY = 8.0f;
        m_lowJumpMoveY = 5.0f;
        m_maxSpeed = 4.0f;
        m_minSpeed = 2.0f;
        m_currentSpeed = (m_maxSpeed - m_minSpeed) / 3 + m_minSpeed;
        m_jumpGradeMagnification = 1.5;
        m_jumpGradeTime = 0.9f;
        m_isTopJumpAction = false;
        m_isBottomJumpAction = false;
        m_isLeftJumpAction = false;
        m_isRightJumpAction = false;
        m_isJump = false;
        m_isJumpAction = false;
        m_rot = m_rotation;
        m_currentJumpActionTime = 0;
        m_jumpActionLimitTime = 0.3;
        m_upSpeedValue = 0.5f;
        m_jumpMissDownSpeedValue = 1.0f;
        m_groundWaveDownSpeedValue = 0.1f;
    }

    void Player::OnCreate() {

        DrawingImage(L"trace.png");
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

        PsBoxParam param(transPtr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
        AddComponent<RigidbodyBox>(param)->SetDrawActive(true);

        AddComponent<CollisionObb>()->SetMakedSize(1);

        //SetTexture(L"");
    }

    void Player::OnUpdate() {
        JudgeJumpAction();
    }

    void Player::OnUpdate2() {
        JumpAction();
    }

    //スピードの上限下限処理
    void Player::AdjustSpeed() {
        if (m_currentSpeed > m_maxSpeed) {
            m_currentSpeed = m_maxSpeed;
        }
        if (m_currentSpeed < m_minSpeed) {
            m_currentSpeed = m_minSpeed;
        }
    }

    //スピードアップ処理
    void Player::SpeedUp(float upSpeedValue) {
        m_currentSpeed += upSpeedValue;
        AdjustSpeed();
    }

    //ジャンプミスのスピードダウン処理
    void Player::JumpMissSpeedDown() {
        m_currentSpeed -= m_jumpMissDownSpeedValue;
        AdjustSpeed();
    }

    //継続スピードダウン処理
    void Player::GroundWaveSpeedDown() {
        m_currentSpeed -= m_groundWaveDownSpeedValue * App::GetApp()->GetElapsedTime();
        AdjustSpeed();
    }

    //ジャンプアクションの入力判定
    void Player::JudgeJumpAction() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        if (m_isJump && Vec2(controller.fThumbLX,controller.fThumbLY).length() >= 1.0f) {
            m_currentJumpActionTime += App::GetApp()->GetElapsedTime();
        }
        if (m_isJump && !m_isJumpAction && m_currentJumpActionTime <= m_jumpActionLimitTime) {
            if (controller.fThumbLY >= 1.0f) {
                m_isTopJumpAction = true;
            }
            if (controller.fThumbLY <= -1.0f) {
                m_isBottomJumpAction = true;
            }
            if (controller.fThumbLX <= -1.0f) {
                m_isLeftJumpAction = true;
            }
            if (controller.fThumbLX >= 1.0f) {
                m_isRightJumpAction = true;
            }
        }
        else {
            m_isTopJumpAction = false;
            m_isBottomJumpAction = false;
            m_isLeftJumpAction = false;
            m_isRightJumpAction = false;
            m_currentJumpActionTime = 0;
        }

        if (m_isTopJumpAction && m_isBottomJumpAction && m_isLeftJumpAction && m_isRightJumpAction && !m_isJumpAction) {
            m_isTopJumpAction = false;
            m_isBottomJumpAction = false;
            m_isLeftJumpAction = false;
            m_isRightJumpAction = false;
            m_isJumpAction = true;
        }
    }

    //ジャンプアクション処理
    void Player::JumpAction() {
        if (m_isJumpAction) {
            m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime();
            GetComponent<Transform>()->SetRotation(m_rot);
            if (m_rot.z >= XM_2PI) {
                m_rot.z = 0;
                m_isJumpAction = false;
            }
        }
    }

    //ジャンプ処理
    void Player::Jump() {
        bool isGreatJump = false;
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();
        if (2.0f/ m_currentSpeed * m_jumpGradeTime<= m_currentJumpGradeTime) {
            isGreatJump = true;
        }
        if (isGreatJump) {
            if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
                SpeedUp(m_upSpeedValue * m_jumpGradeMagnification);
                HighJump();
                m_currentJumpGradeTime = 0;

            }
            if (controller.wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
                SpeedUp(m_upSpeedValue * m_jumpGradeMagnification);
                LowJump();
                m_currentJumpGradeTime = 0;

            }
        }
        else{
            if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
                SpeedUp(m_upSpeedValue);
                HighJump();
                m_currentJumpGradeTime = 0;

            }
            if (controller.wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
                SpeedUp(m_upSpeedValue);
                LowJump();
                m_currentJumpGradeTime = 0;

            }
        }
    }

    //ハイジャンプ
    void Player::HighJump() {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_highJumpMoveY, 0));
    }

    //ロージャンプ
    void Player::LowJump() {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_lowJumpMoveY, 0));
    }

    //コリジョンの最初に当たった瞬間１回のみの処理
    void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"GroundWave")) {
            m_isJump=false;
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
    }

    //コリジョンに当たり続けているときの処理
    void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Wave")) {
            Jump();
        }
        //落下防止処理
        if (other->FindTag(L"GroundWave")&&!m_isJump) {
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
            GroundWaveSpeedDown();
        }
    }

    //コリジョンから抜けた瞬間１回のみの処理
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {
        if (other->FindTag(L"Wave") && !m_isJump) {
            JumpMissSpeedDown();
            m_currentJumpGradeTime = 0;
        }
    }
}
//end basecross

