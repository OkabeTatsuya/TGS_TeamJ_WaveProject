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
    {}

    //メンバ変数の初期化
    void Player::Initialize()
    {
        m_initRotation = m_rotation;
        m_initPosition = m_position;
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

    }

    void Player::OnUpdate2() {
        auto transPtr=GetComponent<Transform>();
        //回転の固定
        transPtr->SetRotation(m_initRotation);
        //落下しないようにする
        if (!m_isJump)
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
    }

    //ジャンプの処理
    void Player::Jump() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec();
        //ボタンの判定
        if (controller[0].wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            HighJump();
        }
        if (controller[0].wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
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

    }
    //コリジョンから抜けた瞬間１回のみの処理
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {

    }
}
//end basecross

