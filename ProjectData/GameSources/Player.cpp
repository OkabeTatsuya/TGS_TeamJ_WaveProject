/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    Player::Player(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {
        m_isFirstJump = false;
        m_currentFlightTime = 0;
        m_maxFlightTime = 0.5f;
        m_currentAnimationKeyCount = 0;
        m_isWaveTouch = false;
        m_jumpActionTime = 0.5f;
        m_highJumpMoveY = 8.0f;
        m_lowJumpMoveY = 5.0f;
        m_maxSpeed = 6.0f;
        m_minSpeed = 2.0f;
        GameManager::GetInstance().SetGameSpeed((m_maxSpeed - m_minSpeed) / 3 + m_minSpeed);
        m_jumpGradeSpeedMagnification = 1.5;
        m_jumpGradeScoreMagnification = 2.0f;
        m_jumpGradeTime = 0.0f;
        m_jumpGradeTimeJudge = 0.9f;
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
        m_jumpMissDownSpeedValue = 0.5f;
        m_groundWaveDownSpeedValue = 0.1f;
        m_currentLandingTime = 0;
        m_maxLandingTime = 0.2;
        m_isLanding = false;
        m_currentInvincibleTime = 0;
        m_maxInvincibleTime = 1.0f;
        m_isInvincible = false;
        m_maxSpeedScoreMagnification = 1.5f;
        m_currentSpeedScoreMagnification = 0;
        m_comboMagnification = 0.1f;
        m_combo = 0;
        m_greatJumpMagnification = 1.5;
        m_maxAnimationTime = 0.1f;
        m_currentAnimationTime = 0.0f;
        m_isWaitingAnimation = true;
        m_isJumpActionZAnimation = false;
        m_isFinishJumpFinishAnimation = false;
        m_isFinishJumpStartAnimation = false;
        m_isJumpFinishAnimation = false;
        m_isJumpStartAnimation = false;
        m_currentSpecialJumpCount = 0;
        m_specialJumpCount = 3;
        m_managerniaruyatu = true;
    }

    void Player::OnCreate() {

        DrawingImage(L"Wait_1.png");
        InitAnimation();
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

        PsBoxParam param(transPtr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
        AddComponent<RigidbodyBox>(param);/*->SetDrawActive(true);*/

        AddComponent<CollisionObb>()->SetMakedSize(Vec3(1.0f));

        m_scoreUpUI = GetStage()->AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(30.0f, 20.0f, 1.0f), Vec2(0.0f), float(2.0f), L"", 4, true);
        GameManager::GetInstance().SetScoreUpUIPanel(m_scoreUpUI);

		AddTag(L"Player");
    }

    void Player::InitAnimation() {
        wstring wait = L"Wait_";
        wstring jumpX = L"JumpX_";
        wstring jumpY = L"JumpY_";
        wstring jumpZ = L"JumpZ";
        wstring jumpStart = L"JumpStart_";
        wstring jumpFinish = L"JumpFinish_";
        wstring number;
        wstring png = L".png";
        for (int i = 0; i < m_waitingAnimationKeyCount; i++) {
            number = to_wstring(i + 1);
            m_waitingAnimationKeys[i] = wait + number + png;
        }
        for (int i = 0; i < m_jumpActionAnimationZKeyCount; i++) {
            number = to_wstring(i + 1);
            m_jumpActionAnimationZKeys[i] = jumpZ + png;
        }
        for (int i = 0; i < m_jumpStartAnimationKeyCount; i++) {
            number = to_wstring(i + 4);
            m_jumpStartAnimationKeys[i] = jumpStart + number + png;
        }
        for (int i = 0; i < m_jumpFinishAnimationKeyCount; i++) {
            number = to_wstring(i + 1);
            m_jumpFinishAnimationKeys[i] = jumpFinish + number + png;
        }
        for (int i = 0; i < m_jumpActionAnimationXKeyCount; i++) {
            number = to_wstring(i + 1);
            m_jumpActionAnimationXKeys[i] = jumpX + number + png;
        }
    }


    void Player::OnUpdate() {
        WaitingAnimation();
        JumpActionZAnimation();
        JumpActionXAnimation();
        JumpStartAnimation();
        JumpFinishAnimation();
        JudgeJumpAction();
        FlightAction();
        Invincible();
        SpeedScoreMagnification();
        m_scoreUpUI->AdjustPosition(GetComponent<Transform>()->GetPosition());
    }

    void Player::OnUpdate2() {
        JumpAction();
    }

    //滞空アニメーション
    void Player::JumpActionXAnimation() {    
        if (m_isJumpActionXAnimation) {
            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationTime >= m_maxAnimationTime) {
                DrawingImage(m_jumpActionAnimationXKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                if (m_currentAnimationKeyCount >= m_jumpActionAnimationXKeyCount) {
                    m_currentAnimationKeyCount = 0;
                    m_isJumpActionXAnimation = false;
                }
                m_currentAnimationTime = 0;
            }
        }
    }

    //ジャンプアクションアニメーション（Y軸）
    void Player::JumpActionYAnimation() {
    }
    //ジャンプアクションアニメーション（Z軸）
    void Player::JumpActionZAnimation() {
        if (m_isJumpActionZAnimation) {
            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationTime >= m_maxAnimationTime) {
                DrawingImage(m_jumpActionAnimationZKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                if (m_currentAnimationKeyCount >= m_jumpActionAnimationZKeyCount) {
                    m_isJumpActionZAnimation = false;
                    m_currentAnimationKeyCount = 0;
                }
                m_currentAnimationTime = 0;
            }
        }
    }

    //待機アニメーション
    void Player::WaitingAnimation() {
        if (m_isWaitingAnimation) {
            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationKeyCount >= m_waitingAnimationKeyCount) {
                m_currentAnimationKeyCount = 0;
            }

            if (m_currentAnimationTime >= m_maxAnimationTime) {
                DrawingImage(m_waitingAnimationKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                m_currentAnimationTime = 0;
            }
        }
    }
    //踏切アニメーション
    void Player::JumpStartAnimation() {
        float jumpStartAnimationFrameTime = 0.03f;
        if (m_isJumpStartAnimation) {
            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationKeyCount >= m_jumpStartAnimationKeyCount) {
                m_isJumpStartAnimation = false;
                DrawingImage(m_jumpStartAnimationKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount = 0;
            }
            if (m_currentAnimationTime >= jumpStartAnimationFrameTime) {
                DrawingImage(m_jumpStartAnimationKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                m_currentAnimationTime = 0;
            }

        }
    }
    //着地アニメーション
    void Player::JumpFinishAnimation() {
        float jumpFinishAnimationFrameTime = 0.05f;
        if (m_isJumpFinishAnimation) {
            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationKeyCount >= m_jumpFinishAnimationKeyCount) {
                m_isFinishJumpStartAnimation = false;
                m_isFinishJumpFinishAnimation = true;
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = false;
                m_isWaitingAnimation = true;
                m_isJumpActionXAnimation = false;
                m_isJumpActionZAnimation = false;
                m_currentAnimationKeyCount = 0;
            }
            if (m_currentAnimationTime >= jumpFinishAnimationFrameTime) {
                DrawingImage(m_jumpFinishAnimationKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                m_currentAnimationTime = 0;
            }
        }
    }
    //スピード依存のスコア倍率計算処理
    void Player::SpeedScoreMagnification() {
        auto diff = m_maxSpeed - m_minSpeed;
        auto currentDiff = GameManager::GetInstance().GetGameSpeed() - m_minSpeed;
        auto currentSpeedPersentage = currentDiff / diff;
        if (diff != currentDiff)
            m_currentSpeedScoreMagnification = 1.0f + 0.5f*currentSpeedPersentage;
        else
            m_currentSpeedScoreMagnification = 1.0f;
    }

    //スピードの上限下限処理
    void Player::AdjustSpeed() {
        auto &gm = GameManager::GetInstance();
        if (gm.GetGameSpeed() > m_maxSpeed) {
            gm.SetGameSpeed(m_maxSpeed);
        }
        if (gm.GetGameSpeed() < m_minSpeed) {
            gm.SetGameSpeed(m_minSpeed);
        }
    }

    //スピードアップ処理
    void Player::SpeedUp(float upSpeedValue) {
        auto &gm = GameManager::GetInstance();
        auto currentSpeed = gm.GetGameSpeed();
        currentSpeed += upSpeedValue;
        gm.SetGameSpeed(currentSpeed);
        AdjustSpeed();
    }

    //ジャンプミスのスピードダウン処理
    void Player::JumpMissSpeedDown() {
        auto &gm = GameManager::GetInstance();
        auto currentSpeed = gm.GetGameSpeed();
        currentSpeed -= m_jumpMissDownSpeedValue;
        gm.SetGameSpeed(currentSpeed);
        AdjustSpeed();
    }

    //継続スピードダウン処理
    void Player::GroundWaveSpeedDown() {
        if (m_isLanding) {
            m_currentLandingTime += App::GetApp()->GetElapsedTime();
            if (m_currentLandingTime >= m_maxLandingTime) {
                m_currentLandingTime = 0;
                m_isLanding = false;
            }
        }
        else {
            auto &gm = GameManager::GetInstance();
            auto currentSpeed = gm.GetGameSpeed();
            currentSpeed -= m_groundWaveDownSpeedValue * App::GetApp()->GetElapsedTime();
            gm.SetGameSpeed(currentSpeed);
            AdjustSpeed();
        }

    }
    //スペシャルジャンプ
    void Player::SpecialJump() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        auto &gm = GameManager::GetInstance();
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();

        if (m_jumpGradeTime * m_jumpGradeTimeJudge <= m_currentJumpGradeTime) {
            m_currentSpecialJumpCount++;
            if (m_currentSpecialJumpCount > m_specialJumpCount) {
                m_isSpecialJump = false;
                m_managerniaruyatu = false;
                m_currentSpecialJumpCount = 0;
            }
            else {
                m_isJumpStartAnimation = true;
                m_isJumpFinishAnimation = false;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionZAnimation = false;
                m_currentAnimationKeyCount = 0;
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                HighJump(m_greatJumpMagnification);
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, false);
                m_currentJumpGradeTime = 0;
                m_combo++;
                m_isJumpAction = true;
                m_isSpecialJump = true;
            }
        }

    }

    //ジャンプアクションの入力判定
    void Player::JudgeJumpAction() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        if (m_isJump && Vec2(controller.fThumbLX, controller.fThumbLY).length() >= 1.0f) {
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
            m_currentAnimationKeyCount = 0;
        }
    }

    //滞空アクション処理
    void Player::FlightAction() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        if (m_isJump && controller.wPressedButtons & XINPUT_GAMEPAD_LEFT_THUMB && m_isEnableFlightAction && GetComponent<RigidbodyBox>()->GetLinearVelocity().y <=0) {
            m_isFlightAction = true;
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
        if (m_isFlightAction) {
            m_isJumpStartAnimation = false;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = true;
            m_isJumpActionZAnimation = false;
            m_currentFlightTime += App::GetApp()->GetElapsedTime();
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0.0f,-0.2f,0.0f));
            if (m_currentFlightTime >= m_maxFlightTime) {
                m_isFlightAction = false;
                m_isEnableFlightAction = false;
                m_currentFlightTime = 0.0f;
                GetComponent<RigidbodyBox>()->SetAutoGravity(true);

            }
        }
    }

    //ジャンプアクション処理
    void Player::JumpAction() {
        if (m_isSpecialJump) {
            if (m_isJumpAction && (m_isSpecialJump && GetComponent<RigidbodyBox>()->GetLinearVelocity().y <= 0)) {
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = false;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionZAnimation = true;
                m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime() / m_jumpActionTime;
                GetComponent<Transform>()->SetRotation(m_rot);
                if (m_rot.z >= XM_2PI) {
                    m_rot.z = 0;
                    m_isJumpAction = false;
                    m_isInvincible = false;
                    GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification);
                }
            }
        }
        else {
            if (m_isJumpAction) {
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = false;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionZAnimation = true;                m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime() / m_jumpActionTime;
                GetComponent<Transform>()->SetRotation(m_rot);
                if (m_rot.z >= XM_2PI) {
                    m_rot.z = 0;
                    m_isJumpAction = false;
                    m_isInvincible = false;
                    GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification);
                }
            }
        }
    }

    //ジャンプ処理
    void Player::Jump() {
        bool isGreatJump = false;
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        auto &gm = GameManager::GetInstance();
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();
        if (m_jumpGradeTime * m_jumpGradeTimeJudge <= m_currentJumpGradeTime) {
            isGreatJump = true;
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            m_isJumpStartAnimation = true;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentAnimationKeyCount = 0;
            if (isGreatJump) {
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                HighJump(m_greatJumpMagnification);
            }
            else {
                SpeedUp(m_upSpeedValue);
                HighJump(1.0f);
            }
            gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification,false);
            m_currentJumpGradeTime = 0;
            m_combo++;
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_B && !m_isJump) {
            m_isJumpStartAnimation = true;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentAnimationKeyCount = 0;
            if (isGreatJump) {
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                LowJump(m_greatJumpMagnification);
            }
            else {
                SpeedUp(m_upSpeedValue);
                LowJump(1.0f);
            }
            m_currentJumpGradeTime = 0;
            gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification,isGreatJump);
            m_combo++;
        }
    }
    

    //ハイジャンプ
    void Player::HighJump(float jumpMag) {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_highJumpMoveY * jumpMag, 0));
        ActiveSE(L"se_maoudamashii_system37.wav");
    }

    //ロージャンプ
    void Player::LowJump(float jumpMag) {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_lowJumpMoveY * jumpMag, 0));
        ActiveSE(L"se_maoudamashii_system37.wav");
    }

    //無敵
    void Player::Invincible() {
        if (m_isInvincible) {
            m_currentInvincibleTime += App::GetApp()->GetElapsedTime();
            if (m_currentInvincibleTime >= m_maxInvincibleTime) {
                m_currentInvincibleTime = 0;
                m_isInvincible = false;
            }
        }
        else {
            m_currentInvincibleTime = 0;
        }
    }

    //効果音
    void Player::ActiveSE(wstring se) {
        auto XAPtr = App::GetApp()->GetXAudio2Manager();
        auto SE = XAPtr->Start(se, 0, 0.5f);
    }

    //コリジョンの最初に当たった瞬間１回のみの処理
    void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Sea")) {
            m_currentAnimationKeyCount = 0;
            m_isEnableFlightAction = true;
            m_isJump=false;
            m_isLanding = true;
            if (m_isFirstJump) {
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = true;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionZAnimation = false;
            }
            if (m_rot.z!=0) {
                JumpMissSpeedDown();
                m_isInvincible = true;
            }
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
        if (other->FindTag(L"Wave")) {
            m_isFirstJump = true;
            float collisionSize = 2.0f;
            auto currentSpeed = GameManager::GetInstance().GetGameSpeed();
            auto a = collisionSize / currentSpeed * m_groundWaveDownSpeedValue;
            auto c = currentSpeed - a;
            auto d = (c + currentSpeed) / 2;
            m_jumpGradeTime = collisionSize / d*m_jumpGradeTimeJudge;
        }
    }

    //コリジョンに当たり続けているときの処理
    void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Wave")) {
            m_isWaveTouch = true;
            if (m_managerniaruyatu) {
                SpecialJump();
            }
            else {
                Jump();
            }
        }
        //落下防止処理
        if (other->FindTag(L"Sea")&&!m_isJump) {
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
            if (!m_isInvincible&&!m_isWaveTouch&&m_isFirstJump) {
                GroundWaveSpeedDown();
            }
        }
    }

    //コリジョンから抜けた瞬間１回のみの処理
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {
        if (other->FindTag(L"Wave") && !m_isJump) {
            if (!m_isInvincible&&m_isFirstJump) {
                JumpMissSpeedDown();
                m_isInvincible = true;
            }
            m_currentJumpGradeTime = 0;
            m_combo = 0;
            m_isWaveTouch = false;
        }
    }
}
//end basecross

