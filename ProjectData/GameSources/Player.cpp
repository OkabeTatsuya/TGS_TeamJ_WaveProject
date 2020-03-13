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
        m_initRotation = m_rotation;
        m_initPosition = m_position;
        m_isTopJumpAction = false;
        m_isBottomJumpAction = false;
        m_isLeftJumpAction = false;
        m_isRightJumpAction = false;
        m_isJump = false;
        m_isJumpAction = false;
        m_rot = m_rotation;
    }

    void Player::OnCreate() {

        DrawingImage(L"trace.png");
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);


        PsBoxParam param(transPtr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);

        AddComponent<RigidbodyBox>(param)->SetDrawActive(true);
        

        AddComponent<CollisionObb>()->SetDrawActive(true);


        //SetTexture(L"");
    }

    void Player::OnUpdate() {
        if (m_isJump && !m_isJumpAction) {
            auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
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

        if (m_isTopJumpAction && m_isBottomJumpAction && m_isLeftJumpAction && m_isRightJumpAction && !m_isJumpAction) {
            m_isTopJumpAction = false;
            m_isBottomJumpAction = false;
            m_isLeftJumpAction = false;
            m_isRightJumpAction = false;
            m_isJumpAction = true;
        }
    }

    void Player::OnUpdate2() {

        if (m_isJumpAction) {

            m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime();
            GetComponent<Transform>()->SetRotation(m_rot);
            if (m_rot.z >= XM_2PI) {
                m_isJumpAction = false;
                m_rot.z = 0;
            }
        }
    }

    //ジャンプの処理
    void Player::Jump() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        //ボタンの判定
        if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            HighJump();
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
            LowJump();
        }

    }

    //高いジャンプ
    void Player::HighJump() {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_highJumpMoveY, 0));

    }

    //低いジャンプ
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
            m_initPosition.y = GetComponent<Transform>()->GetPosition().y;
        }
    }
    //コリジョンに当たり続けているときの処理
    void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Wave")) {
            Jump();
        }
        if (other->FindTag(L"GroundWave")&&!m_isJump) {
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
        }

    }
    //コリジョンから抜けた瞬間１回のみの処理
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {

    }
}
//end basecross

