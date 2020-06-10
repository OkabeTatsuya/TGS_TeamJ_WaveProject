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
        Vec3& position,
		int&  layer) :

        ObjectBase(stage,
            rotation, scale, position, layer
        )
    {
        m_jumpActionDif = 0.8f;
        m_isFirstJump = false;
        m_currentFlightTime = 0;
        m_maxFlightTime = 0.5f;
        m_currentAnimationKeyCount = 0;
        m_isWaveTouch = false;
        m_jumpActionTime = 0.5f;
        m_highJumpMoveY = 7.5f;
        m_midJumpMoveY = 5.5f;
        m_lowJumpMoveY = 4.0f;
        m_maxSpeed = 6.0f;
        m_minSpeed = 3.0f;
        GameManager::GetInstance().SetGameSpeed((m_maxSpeed - m_minSpeed) / 3 + m_minSpeed);
        m_jumpGradeSpeedMagnification = 1.5;
        m_jumpGradeScoreMagnification = 2.0f;
        m_jumpGradeTime = 0.0f;
        m_jumpGradeTimeJudge = 0.8f;
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
        m_invincibleFlashSpeed = 0.25f;
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
        m_specialJumpActionMaxCount = 2;
        m_knockBackValue = 0.5f;

		m_playerVoiceStr = { L"Voice2_1.wav", L"Voice2_3.wav", L"Voice2_4.wav"};
		m_playerSpecialVoiceStr = { L"Voice2_6.wav", L"Voice2_10.wav"};
    }

    void Player::OnCreate() {


        DrawingImage(L"Wait_1.png");
        InitAnimation();
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

        PsBoxParam param(transPtr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
        AddComponent<RigidbodyBox>(param);

        auto colPtr = AddComponent<CollisionObb>();
        colPtr->SetMakedSize(Vec3(1.0f, 1.0f, 1.0f));

        m_scoreUpUI = GetStage()->AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(30.0f, 20.0f, 1.0f), Vec2(0.0f), float(7.0f), L"Number.png", 4, true);
        GameManager::GetInstance().SetScoreUpUIPanel(m_scoreUpUI);

		AddTag(L"Player");

		m_effectObj = GetStage()->AddGameObject<EffectObject>();
		m_effectObj->GetComponent<Transform>()->SetPosition(Vec3(0.0f));

		m_judgJumpUI = GetStage()->AddGameObject<JudgJumpUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), Vec2(0.0f), float(7.0f), L"Perfect.png");

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
        for (int i = 0; i < m_jumpActionAnimationYKeyCount; i++) {
            number = to_wstring(i + 1);
            m_jumpActionAnimationYKeys[i] = jumpY + number + png;
        }
    }


    void Player::OnUpdate() {
        InvincibleAnimation();
        WaitingAnimation();
        JumpActionXAnimation();
        JumpActionYAnimation();
        JumpActionZAnimation();
        JumpStartAnimation();
        JumpFinishAnimation();
        JudgeJumpAction();
        SpecialJumpAction();
        FlightAction();
        Invincible();
        SpeedScoreMagnification();
        GravityControl();
        KnockBack();
        m_scoreUpUI->AdjustPosition(GetComponent<Transform>()->GetPosition());
		m_judgJumpUI->SetingPos(GetComponent<Transform>()->GetPosition());
		FollowEffect();
		SpecialCheck();
    }

    void Player::OnUpdate2() {
        JumpAction();
    }

    //滞空アニメーション
    void Player::JumpActionXAnimation() {    
        if (m_isJumpActionXAnimation) {
			JumpAcionEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
			m_animeTimeCounter += App::GetApp()->GetElapsedTime();

            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationTime >= m_maxAnimationTime) {
                DrawingImage(m_jumpActionAnimationXKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                if (m_currentAnimationKeyCount >= m_jumpActionAnimationXKeyCount) {
					m_animeTimeCounter = 0;
                    m_currentAnimationKeyCount = 0;
                    m_isJumpActionXAnimation = false;
                    if (m_isSpecialJumpAction) {
                        m_currentSpecialJumpActionCount++;
                    }
                }
                m_currentAnimationTime = 0;
            }
        }
    }

    //ジャンプアクションアニメーション（Y軸）
    void Player::JumpActionYAnimation() {
        if (m_isJumpActionYAnimation) {
			JumpAcionEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
			m_animeTimeCounter += App::GetApp()->GetElapsedTime();

            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_currentAnimationTime >= m_maxAnimationTime) {
                DrawingImage(m_jumpActionAnimationYKeys[m_currentAnimationKeyCount]);
                m_currentAnimationKeyCount++;
                if (m_currentAnimationKeyCount >= m_jumpActionAnimationYKeyCount) {
                    m_isJumpActionYAnimation = false;
					m_animeTimeCounter = 0;
                    m_currentAnimationKeyCount = 0;
					GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification, JumpActionType::en_ActionY);

                    if (m_isSpecialJumpAction) {
                        m_currentSpecialJumpActionCount++;
                    }
                }
                m_currentAnimationTime = 0;
            }
        }

    }
    //ジャンプアクションアニメーション（Z軸）
    void Player::JumpActionZAnimation() {
        if (m_isJumpActionZAnimation) {
			JumpAcionEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
			m_animeTimeCounter += App::GetApp()->GetElapsedTime();

            m_currentAnimationTime += App::GetApp()->GetElapsedTime();
            if (m_isInvincible) {
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = true;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionYAnimation = false;
                m_isJumpActionZAnimation = false;
            }
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
                m_isJumpActionYAnimation = false;
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

    //無敵アニメーション
    void Player::InvincibleAnimation() {
        if (m_isInvincible) {
            auto drawPtr = GetComponent<PCTStaticDraw>();
            auto color = drawPtr->GetDiffuse();
            float flashSpeed = m_currentInvincibleTime / m_invincibleFlashSpeed;

            if (flashSpeed <= 0.3f || flashSpeed>=XM_PI) {
                flashSpeed = 0.3f;
            }

            color.w = sinf(flashSpeed);

            drawPtr->SetDiffuse(color);
        }
        else {
            auto drawPtr = GetComponent<PCTStaticDraw>();
            auto color = drawPtr->GetDiffuse();

            color.w = 1.0f;
            drawPtr->SetDiffuse(color);

        }
    }

    //重力制御
    void Player::GravityControl()
    {
        if (GameManager::GetInstance().GetIsSpecialTime() && GetComponent<RigidbodyBox>()->GetLinearVelocity().y<0 && !m_isTouchSea && m_isBigWaveJump){
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
            auto gravity = GetComponent<RigidbodyBox>()->GetLinearVelocity();
            gravity.y -= 3.0f * App::GetApp()->GetElapsedTime();
            GetComponent<RigidbodyBox>()->SetLinearVelocity(gravity);

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


    //スペシャルジャンプアクション
    void Player::SpecialJumpAction() {
        if (m_isSpecialJumpAction&&m_currentSpecialJumpActionCount<m_specialJumpActionMaxCount) {
            switch (0) {
            case 0:
                m_isJumpAction = true;
                break;
            case 1:
                m_isFlightAction = true;
                break;
            case 2:
                m_isJumpActionYAnimation = true;
                break;
            default:
                break;
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
            if (controller.fThumbLY >= m_jumpActionDif) {
                m_isTopJumpAction = true;
            }
            if (controller.fThumbLY <= -m_jumpActionDif) {
                m_isBottomJumpAction = true;
            }
            if (controller.fThumbLX <= -m_jumpActionDif) {
                m_isLeftJumpAction = true;
            }
            if (controller.fThumbLX >= m_jumpActionDif) {
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
        if (m_isJump && m_isLeftJumpAction&&m_isRightJumpAction && !m_isTopJumpAction && !m_isBottomJumpAction) {
            m_isLeftJumpAction = false;
            m_isRightJumpAction = false;
            m_isJumpStartAnimation = false;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionYAnimation = true;
            m_isJumpActionZAnimation = false;
        }
    }

    //滞空アクション処理
    void Player::FlightAction() {
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        if (m_isJump && controller.wPressedButtons & XINPUT_GAMEPAD_LEFT_THUMB && m_isEnableFlightAction && GetComponent<RigidbodyBox>()->GetLinearVelocity().y <=0) {
            m_isFlightAction = true;
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
        if (m_isFlightAction && !m_isTouchSea) {
            m_isJumpStartAnimation = false;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = true;
            m_isJumpActionYAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentFlightTime += App::GetApp()->GetElapsedTime();
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0.0f,-0.2f,0.0f));
            if (m_currentFlightTime >= m_maxFlightTime) {
                m_isFlightAction = false;
                m_isEnableFlightAction = false;
                m_currentFlightTime = 0.0f;
				GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification, JumpActionType::en_ActionX);
                GetComponent<RigidbodyBox>()->SetAutoGravity(true);
            }
        }
    }

    //ジャンプアクション処理
    void Player::JumpAction() {
        if (m_isSpecialJumpAction) {
            if (m_isJumpAction && GetComponent<RigidbodyBox>()->GetLinearVelocity().y <= 0) {
                if (!m_isInvincible) {
                    m_isJumpStartAnimation = false;
                    m_isJumpFinishAnimation = false;
                    m_isWaitingAnimation = false;
                    m_isJumpActionXAnimation = false;
                    m_isJumpActionYAnimation = false;
                    m_isJumpActionZAnimation = true;
                }
                m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime() / m_jumpActionTime;
                GetComponent<Transform>()->SetRotation(m_rot);
				if (m_rot.z >= XM_2PI) {
                    m_rot.z = 0;
                    m_isJumpAction = false;
                    m_isInvincible = false;
					m_animeTimeCounter = 0;
                    GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification, JumpActionType::en_ActionZ);
					GameManager::GetInstance().SetIsSpecialJump(true);
				}
                    m_currentSpecialJumpActionCount++;
                }
        }
        else {
            if (m_isJumpAction) {
                if (!m_isInvincible) {
                    m_isJumpStartAnimation = false;
                    m_isJumpFinishAnimation = false;
                    m_isWaitingAnimation = false;
                    m_isJumpActionXAnimation = false;
                    m_isJumpActionYAnimation = false;
                    m_isJumpActionZAnimation = true;
                }
                m_rot.z += XM_2PI * App::GetApp()->GetElapsedTime() / m_jumpActionTime;
                GetComponent<Transform>()->SetRotation(m_rot);
                if (m_rot.z >= XM_2PI) {
                    m_rot.z = 0;
                    m_isJumpAction = false;
                    m_isInvincible = false;
					m_animeTimeCounter = 0;
                    GameManager::GetInstance().AddActionScore(m_currentSpeedScoreMagnification, m_combo * m_comboMagnification, JumpActionType::en_ActionZ);
                }
            }
        }
    }
    //大波のジャンプ処理
    void Player::BigWaveJump() {
        bool isGreatJump = false;
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        auto &gm = GameManager::GetInstance();
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();
        if (m_jumpGradeTime <= m_currentJumpGradeTime) {
            isGreatJump = true;
        }
        if (gm.GetIsSpecialTime() && controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            m_isBigWaveJump = true;
            m_isTouchSea = false;
            m_currentSpecialJumpCount++;
            if (m_currentSpecialJumpCount > m_specialJumpCount) {
                m_isSpecialJump = false;
                m_managerniaruyatu = false;
                m_currentSpecialJumpCount = 0;
            }
            m_isJumpStartAnimation = true;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionYAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentAnimationKeyCount = 0;
            if (isGreatJump) {
                m_knockBackMagnification = 4.0f;
                InitKnockBack(m_knockBackMagnification);
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                HighJump(m_greatJumpMagnification);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, true);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Perfect.png", pos);
            }
            else {
                SpeedUp(m_upSpeedValue);
                HighJump(1.0f);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint17.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, false);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Good.png", pos);
            }
            m_currentJumpGradeTime = 0;
            m_combo++;
			gm.SetIsJumpBigWave(true);
        }
    }

    //中波のジャンプ処理
    void Player::MidWaveJump() {
        bool isGreatJump = false;
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        auto &gm = GameManager::GetInstance();
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();
        if (m_jumpGradeTime <= m_currentJumpGradeTime) {
            isGreatJump = true;
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            m_isTouchSea = false;
            m_isJumpStartAnimation = true;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionYAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentAnimationKeyCount = 0;
            if (isGreatJump) {
                m_knockBackMagnification = 2.0f;
                InitKnockBack(m_knockBackMagnification);
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                MidJump(m_greatJumpMagnification);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, true);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Perfect.png", pos);
            }
            else {
                SpeedUp(m_upSpeedValue);
                MidJump(1.0f);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint17.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, false);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Good.png", pos);
            }
            m_currentJumpGradeTime = 0;
            m_combo++;
        }

    }

    //小波のジャンプ処理
    void Player::SmallWaveJump() {
        bool isGreatJump = false;
        auto controller = App::GetApp()->GetInputDevice().GetControlerVec()[0];
        auto &gm = GameManager::GetInstance();
        m_currentJumpGradeTime += App::GetApp()->GetElapsedTime();
        if (m_jumpGradeTime <= m_currentJumpGradeTime) {
            isGreatJump = true;
        }
        if (controller.wPressedButtons & XINPUT_GAMEPAD_A && !m_isJump) {
            m_isTouchSea = false;
            m_isJumpStartAnimation = true;
            m_isJumpFinishAnimation = false;
            m_isWaitingAnimation = false;
            m_isJumpActionXAnimation = false;
            m_isJumpActionYAnimation = false;
            m_isJumpActionZAnimation = false;
            m_currentAnimationKeyCount = 0;
            if (isGreatJump) {
                m_knockBackMagnification = 1.0f;
                InitKnockBack(m_knockBackMagnification);
                SpeedUp(m_upSpeedValue * m_jumpGradeSpeedMagnification);
                LowJump(m_greatJumpMagnification);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint16.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, true);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Perfect.png", pos);
            }
            else {
                SpeedUp(m_upSpeedValue);
                LowJump(1.0f);
                JumpEffect(EN_EffectName::en_GoodEffect, L"se_maoudamashii_onepoint17.wav");
                gm.AddJumpScore(m_currentSpeedScoreMagnification, m_combo*m_comboMagnification, false);

                Vec3 pos = GetComponent<Transform>()->GetPosition();
                m_judgJumpUI->VisibleUI(L"Good.png", pos);
            }
            m_currentJumpGradeTime = 0;
            m_combo++;
        }
    }


    //ハイジャンプ
    void Player::HighJump(float jumpMag) {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_highJumpMoveY * jumpMag, 0));
    }

    //ミドルジャンプ
    void Player::MidJump(float jumpMag) {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_midJumpMoveY * jumpMag, 0));
    }

    //ロージャンプ
    void Player::LowJump(float jumpMag) {
        m_isJump = true;
        GetComponent<RigidbodyBox>()->SetAutoGravity(true);
        GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, m_lowJumpMoveY * jumpMag, 0));
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

    //ノックバック処理初期化
    void Player::InitKnockBack(float mag) {
        if (m_isTouchSea) {
            m_knockBackPos = GetComponent<Transform>()->GetPosition().x - mag * m_knockBackValue;
            m_isKnockBack = true;
        }
        else {
            m_knockBackPos = GetComponent<Transform>()->GetPosition().x + mag * m_knockBackValue;
            if (m_knockBackPos >= -2.0f) 
                m_knockBackPos = -2.0f;
            else
            m_isKnockUp = true;
        }
    }

    //ノックバック処理
    void Player::KnockBack() {
        if (m_isKnockBack) {
            auto linerVel = GetComponent<RigidbodyBox>()->GetLinearVelocity();
            linerVel.x = -3.0f;
            GetComponent<RigidbodyBox>()->SetLinearVelocity(linerVel);
            if (GetComponent<Transform>()->GetPosition().x <= m_knockBackPos) {
                m_isKnockBack = false;
            }
        }
        if (m_isKnockUp && m_isTouchSea) {
            auto linerVel = GetComponent<RigidbodyBox>()->GetLinearVelocity();
            linerVel.x = +1.0f;
            GetComponent<RigidbodyBox>()->SetLinearVelocity(linerVel);
            if (GetComponent<Transform>()->GetPosition().x >= m_knockBackPos) {
                linerVel.x = 0.0f;
                GetComponent<RigidbodyBox>()->SetLinearVelocity(linerVel);
                m_isKnockUp = false;
            }
        }
    }

	void Player::SpecialCheck() {
		if (m_isTouchSea) {
			auto& gameManager = GameManager::GetInstance();
			gameManager.SpecialCheck();

			if (gameManager.GetIsSpecialTime()) {
				gameManager.SetIsSpecialJump(false);
			}

			if (gameManager.GetIsJumpBigWave()) {
				gameManager.SetIsSpecialTime(false);
				gameManager.SetIsJumpBigWave(false);
			}
		}
	}

    //効果音
    void Player::ActiveSE(wstring se) {
		float pitch = m_combo == 0.0f ? 1.0f : m_combo / 10.0f + 1.0f;
        auto XAPtr = App::GetApp()->GetXAudio2Manager();	
		m_SE = XAPtr->MyStart(se, 0, 0.5f, pitch);
    }

	void Player::PlayVoiceSE(float vol) {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		auto &gameManager = GameManager::GetInstance();

		std::random_device rando;
		std::mt19937 mt(rando());
		int voiceItr = mt() % m_playerSpecialVoiceStr.size();
		int spVoiceItr = mt() % m_playerVoiceStr.size();

		bool JumpAcionFlag = (m_isJumpActionXAnimation || m_isJumpActionYAnimation || m_isJumpActionZAnimation);
		if (!JumpAcionFlag) {
			if (gameManager.GetIsSpecialTime()) {
				m_voiceSE = XAPtr->Start(m_playerSpecialVoiceStr[voiceItr], 0, vol);
			}
			else
			{
				m_voiceSE = XAPtr->Start(m_playerVoiceStr[spVoiceItr], 0, vol);
			}
		}
	}

	//エフェクトの再生
	void Player::JumpEffect(EN_EffectName effectName, wstring seName) {
		auto pos = GetComponent<Transform>()->GetPosition();
		m_effectObj->PlayEffect(EN_EffectName::en_GoodEffect, EffectType::en_Jump, Vec3(pos.x, pos.y, -10.0f));
		ActiveSE(seName);
		PlayVoiceSE(0.5f);
	}

	void Player::JumpAcionEffect(EN_EffectName effectName, wstring seName) {
		bool JumpAcionFlag = (m_isJumpActionXAnimation || m_isJumpActionYAnimation || m_isJumpActionZAnimation);
		
		if (JumpAcionFlag && m_animeTimeCounter == 0) {
			JumpEffect(effectName, seName);
		}
	};

	void Player::SetUpSpecialJumpFlag() {
		bool isSpecialTime = GameManager::GetInstance().GetIsSpecialTime();
		if (isSpecialTime) {
			GameManager::GetInstance().SetIsSpecialJump(true);
		}
	}

	void Player::FollowEffect() {
		if (m_effectObj) {
			auto pos = GetComponent<Transform>()->GetPosition();
			auto efkPlay = m_effectObj->GetEfkPlay(EffectType::en_Jump);
			if (efkPlay != NULL) {
				efkPlay->SetPosition(Vec3(pos.x, pos.y, -10.0f));
				m_effectObj->SetEfkPlay(efkPlay, EffectType::en_Jump);
			}
		}
	};

    //コリジョンの最初に当たった瞬間１回のみの処理
    void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"Sea")) {
            m_isTouchSea = true;
            if (m_isSpecialJumpAction) {
                m_isSpecialJumpAction = false;
                m_currentSpecialJumpActionCount = 0;
            }
            m_currentAnimationKeyCount = 0;
            m_isEnableFlightAction = true;
            m_isJump=false;
            m_isLanding = true;
            if (m_isFirstJump) {
                m_isJumpStartAnimation = false;
                m_isJumpFinishAnimation = true;
                m_isWaitingAnimation = false;
                m_isJumpActionXAnimation = false;
                m_isJumpActionYAnimation = false;
                m_isJumpActionZAnimation = false;
            }
            if (m_rot.z!=0) {
                m_knockBackMagnification = 0.5f;
                InitKnockBack(m_knockBackMagnification);
                JumpMissSpeedDown();
                m_isInvincible = true;
            }
            if (m_isFlightAction) {
                m_isFlightAction = false;
                //m_currentFlightTime = m_maxFlightTime;
            }
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
        }
        if ((other->FindTag(L"SmallWave") || other->FindTag(L"MidWave") || other->FindTag(L"BigWave"))) {
            m_isFirstJump = true;
            float playerColSize = 1.0f;
            float inSpeed = GameManager::GetInstance().GetGameSpeed();
            float stayTime = playerColSize / inSpeed;
            float outSpeed = inSpeed + m_groundWaveDownSpeedValue * stayTime;
            float averageSpeed = (inSpeed + outSpeed) / 2;
            stayTime = playerColSize / averageSpeed;
            m_jumpGradeTime = stayTime * m_jumpGradeTimeJudge;
        }
    }

    //コリジョンに当たり続けているときの処理
    void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
        if (other->FindTag(L"BigWave")) {
            m_isWaveTouch = true;
            BigWaveJump();
        }
        if (other->FindTag(L"MidWave")) {
            m_isWaveTouch = true;
            MidWaveJump();
        }
        if (other->FindTag(L"SmallWave")) {
            m_isWaveTouch = true;
            SmallWaveJump();
        }
        //落下防止処理
        if (other->FindTag(L"Sea") && !m_isJump) {
            GetComponent<RigidbodyBox>()->SetLinearVelocity(Vec3(0, 0, 0));
            GetComponent<RigidbodyBox>()->SetAutoGravity(false);
            if (m_isBigWaveJump) {
                m_isBigWaveJump = false;
            }
            if (!m_isInvincible && !m_isWaveTouch&&m_isFirstJump) {
                m_isTouchSea = true;

                GroundWaveSpeedDown();
            }
			bool JumpAcionFlag = (m_isJumpActionXAnimation || m_isJumpActionYAnimation || m_isJumpActionZAnimation);

			if (JumpAcionFlag) {
				m_combo = 0;
			}
        }
    }

    //コリジョンから抜けた瞬間１回のみの処理
    void Player::OnCollisionExit(shared_ptr<GameObject>&other) {
        if (other->FindTag(L"BigWave")&&m_isTouchSea) {
            if (!m_isInvincible&&m_isFirstJump) {
                m_knockBackMagnification = 4.0f;
                InitKnockBack(m_knockBackMagnification);
                JumpMissSpeedDown();
				GameManager::GetInstance().SetIsSpecialTime(false);
                m_isInvincible = true;
            }
            m_currentJumpGradeTime = 0;
            m_combo = 0;
            m_isWaveTouch = false;
        }
        if (other->FindTag(L"MidWave") && m_isTouchSea) {
            if (!m_isInvincible&&m_isFirstJump) {
                m_knockBackMagnification = 2.0f;
                InitKnockBack(m_knockBackMagnification);
                JumpMissSpeedDown();
                m_isInvincible = true;
            }
            m_currentJumpGradeTime = 0;
            m_combo = 0;
            m_isWaveTouch = false;
        }
        if (other->FindTag(L"SmallWave")&&m_isTouchSea) {
            if (!m_isInvincible&&m_isFirstJump) {
                m_knockBackMagnification = 1.0f;
                InitKnockBack(m_knockBackMagnification);
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

