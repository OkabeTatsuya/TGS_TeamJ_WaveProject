/*!
@file Player.cpp
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«é¿ëÃ
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
    {}

    void Player::Initialize()
    {
        m_initRotation = m_rotation;
        m_isJump = true;
    }

    void Player::OnCreate() {

        Initialize();
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
        //âÒì]ÇÃå≈íË
        GetComponent<RigidbodyBox>()->SetAngularVelocity(m_initRotation);

        Jump();
    }

    void Player::Jump() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec();
        if (controller[0].wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            HighJump();
        }
        if (controller[0].wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
            LowJump();
        }

    }

    void Player::HighJump() {
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 8, 0));
        m_isJump = true;

    }

    void Player::LowJump() {
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 5, 0));
        m_isJump = true;

    }

    void Player::OnCollisionEnter(shared_ptr<GameObject>& gameobject) {
        if (gameobject->FindTag(L"GroundWave")) {
            m_isJump=false;
        }
    }

}
//end basecross

