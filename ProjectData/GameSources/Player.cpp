/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
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
        m_highJumpMoveY = 8;
        m_lowJumpMoveY = 5;
        m_maxSpeed = 4;
        m_minSpeed = 2;
        m_currentSpeed = (m_maxSpeed - m_minSpeed) / 3 + m_minSpeed;
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
        

        AddComponent<CollisionObb>()->SetDrawActive(true);


        //SetTexture(L"");
    }

    void Player::OnUpdate() {
        JudgeJumpAction();
    }

    void Player::OnUpdate2() {
        JumpAction();
    }

    //�X�s�[�h�̏�������̌��E�ݒ�
    void Player::AdjustSpeed() {
        if (m_currentSpeed > m_maxSpeed) {
            m_currentSpeed = m_maxSpeed;
        }
        if (m_currentSpeed < m_minSpeed) {
            m_currentSpeed = m_minSpeed;
        }
    }

    //�X�s�[�hUP
    void Player::SpeedUp() {
        m_currentSpeed += m_upSpeedValue;
        AdjustSpeed();
    }
    //�W�����v�~�X�����Ƃ��̃X�s�[�hDOWN
    void Player::JumpMissSpeedDown() {
        m_currentSpeed -= m_jumpMissDownSpeedValue;
        AdjustSpeed();
    }
    //�n�ʂƂȂ�g�ɓ������Ă���Ƃ��̌p���I�ȃX�s�[�h�_�E��
    void Player::GroundWaveSpeedDown() {
        m_currentSpeed -= m_groundWaveDownSpeedValue * App::GetApp()->GetElapsedTime();
        AdjustSpeed();
    }
    //�W�����v�A�N�V�����̓��͔���
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

    //�W�����v�A�N�V����
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

    //�W�����v�̏���
    void Player::Jump() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        //�{�^���̔���
        if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            SpeedUp();
            HighJump();
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
            SpeedUp();
            LowJump();
        }

    }

    //�����W�����v
    void Player::HighJump() {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_highJumpMoveY, 0));

    }

    //�Ⴂ�W�����v
    void Player::LowJump() {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_lowJumpMoveY, 0));

    }

    //�R���W�����̍ŏ��ɓ��������u�ԂP��݂̂̏���
    void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"GroundWave")) {
            m_isJump=false;
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
    }
    //�R���W�����ɓ����葱���Ă���Ƃ��̏���
    void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Wave")) {
            Jump();
        }
        //�����h�~����
        if (other->FindTag(L"GroundWave")&&!m_isJump) {
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
            GroundWaveSpeedDown();
        }

    }
    //�R���W�������甲�����u�ԂP��݂̂̏���
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {
        if (other->FindTag(L"Wave") && !m_isJump) {
            JumpMissSpeedDown();
        }
    }
}
//end basecross

