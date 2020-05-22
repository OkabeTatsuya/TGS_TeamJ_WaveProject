/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
        //�W�����v���؋�A�N�V�����̍ő厞��
        float m_maxFlightTime;
        //���݂̃W�����v���؋�A�N�V�����̎���
        float m_currentFlightTime;
        //�؋�A�N�V�����t���O
        bool m_isFlightAction;
        //�؋�A�N�V�����A���s�g�p�t���O
        bool m_isEnableFlightAction;
        //�W�����v�A�N�V�����̂P��]�ɂ����鎞��
        float m_jumpActionTime;
        //�W�����v�̃t���O
        bool m_isJump = true;
        //�n�C�W�����v�̏㏸��
        float m_highJumpMoveY;
        //���[�W�����v�̏㏸��
        float m_lowJumpMoveY;
        //�ǃW�����v���̃W�����v�̏㏸�ʔ{��
        float m_greatJumpMagnification;
        //�ړ����x���
        float m_maxSpeed;
        //�ړ����x����
        float m_minSpeed;
        //�p���X�s�[�h�_�E���̌�����
        float m_groundWaveDownSpeedValue;
        //�g�ɓ������Ă���Ƃ��̔���
        bool m_isWaveTouch;
        //���݂̃W�����v�̃O���[�h����b��
        float m_currentJumpGradeTime;
        //�ǃW�����v�������̃X�s�[�h�̏㏸�ʔ{��
        float m_jumpGradeSpeedMagnification;
        //�ǃW�����v�����Ƃ��̃X�R�A�̏㏸�ʔ{��
        float m_jumpGradeScoreMagnification;
        //�X�s�[�h�Ɉˑ������X�R�A�̔{�����
        float m_maxSpeedScoreMagnification;
        //���݂̃X�s�[�h�Ɉˑ������X�R�A�̔{��
        float m_currentSpeedScoreMagnification;
        //�W�����v�O���[�h���莞��
        float m_jumpGradeTime;
        //�W�����v�O���[�h����̓�Փx
        float m_jumpGradeTimeJudge;
        //�󒆃A�N�V��������
        bool m_isJumpAction;
        //�󒆃A�N�V�������̃X�e�B�b�N�㉺���E�F���t���O
        bool m_isTopJumpAction;
        bool m_isBottomJumpAction;
        bool m_isLeftJumpAction;
        bool m_isRightJumpAction;
        //�󒆃A�N�V�����̓��͎���
        float m_jumpActionLimitTime;
        //���݂̋󒆃A�N�V�����̓��͂ɂ������Ă��鎞��
        float m_currentJumpActionTime;
        //�W�����v�����Ƃ��̃X�s�[�h�̏㏸��
        float m_upSpeedValue;
        //�W�����v�~�X�����Ƃ��̃X�s�[�h�̌�����
        float m_jumpMissDownSpeedValue;
        //�W�����v�㒅�n�����Ƃ��̃X�s�[�h�ێ�����
        bool m_isLanding;
        //�W�����v�㒅�n�����Ƃ��̃X�s�[�h�ێ�����������
        float m_maxLandingTime;
        //���݂̃W�����v�㒅�n�����Ƃ��̃X�s�[�h�ێ����莞��
        float m_currentLandingTime;
        //�W�����v�~�X�܂��͒��n�~�X�����Ƃ��̖��G���ԏ��
        float m_maxInvincibleTime;
        //���݂̃W�����v�~�X�܂��͒��n�~�X�����Ƃ��̖��G����
        float m_currentInvincibleTime;
        //�W�����v�~�X�܂��͒��n�~�X�����Ƃ��̖��G����
        bool m_isInvincible;
        //�A���Ŕg�ɏ���Ă����
        int m_combo;
        //�P�R���{�ő�����{��
        float m_comboMagnification;
        //�X�R�A�A�b�vUI
        shared_ptr<ScoreUIPanel> m_scoreUpUI;
        //�ŏ��̃W�����v����܂Ō������~�߂�
        bool m_isFirstJump;
        //���݂̃A�j���[�V�����̕\���R�}
        int m_currentAnimationKeyCount;
        //�A�j���[�V�����P�R�}�ɑ΂���t���[����
        float m_maxAnimationTime;
        //���݂̃A�j���[�V�����̃t���[����
        float m_currentAnimationTime;
        //�ҋ@�A�j���[�V�����̃R�}��
        static const int m_waitingAnimationKeyCount = 11;
        //�ҋ@�A�j���[�V�����ڍs�t���O
        bool m_isWaitingAnimation;
        //���؃A�j���[�V�����ڍs�t���O
        bool m_isJumpStartAnimation;
        //���؃A�j���[�V���������t���O
        bool m_isFinishJumpStartAnimation;
        //���n�A�j���[�V�����ڍs�t���O
        bool m_isJumpFinishAnimation;
        //���n�A�j���[�V���������t���O
        bool m_isFinishJumpFinishAnimation;
        //�W�����v�A�N�V�����A�j���[�V�����iZ���j�ڍs�t���O
        bool m_isJumpActionZAnimation;
        //�W�����v�A�N�V�����A�j���[�V�����iX���j�ڍs�t���O
        bool m_isJumpActionXAnimation;
        //�ҋ@�A�j���[�V������key
        wstring m_waitingAnimationKeys[m_waitingAnimationKeyCount];
        //�W�����v�A�N�V����X���A�j���[�V�����̃R�}��
        static const int m_jumpActionAnimationXKeyCount = 8;
        //�W�����v�A�N�V����X���A�j���[�V������key
        wstring m_jumpActionAnimationXKeys[m_jumpActionAnimationXKeyCount];
        //�W�����v�A�N�V����Z���A�j���[�V�����̃R�}��
        static const int m_jumpActionAnimationZKeyCount = 1;
        //�W�����v�A�N�V����Z���A�j���[�V������key
        wstring m_jumpActionAnimationZKeys[m_jumpActionAnimationZKeyCount];
        //�W�����v�X�^�[�g�A�j���[�V�����R�}��
        static const int m_jumpStartAnimationKeyCount = 5;
        //�W�����v�X�^�[�g�A�j���[�V������key
        wstring m_jumpStartAnimationKeys[m_jumpStartAnimationKeyCount];
        //�W�����v�t�B�j�b�V���A�j���[�V�����R�}��
        static const int m_jumpFinishAnimationKeyCount = 7;
        //�W�����v�t�B�j�b�V���A�j���[�V������key
        wstring m_jumpFinishAnimationKeys[m_jumpFinishAnimationKeyCount];
        //�X�y�V�����W�����v��
        int m_specialJumpCount;
        //���݂̃X�y�V�����W�����v�̉�
        int m_currentSpecialJumpCount;
        //�X�y�V�����W�����v���t���O
        bool m_isSpecialJump;

		shared_ptr<EffectObject> m_effectObj;
		shared_ptr<JudgJumpUI> m_judgJumpUI;

    private:
        //�v���C���[�̊p�x
        Vec3 m_rot;
    public:
        Player(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        virtual void OnUpdate2()override;
        //�R���W�����̍ŏ��ɓ��������u�ԂP��݂̂̏���
        virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
        //�R���W�����ɓ����葱���Ă���Ƃ��̏���
        virtual void OnCollisionExcute(shared_ptr<GameObject>& other) override;
        //�R���W�������甲�����u�ԂP��݂̂̏���
        virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;
        //�W�����v
        void Jump();
        //�n�C�W�����v
        void HighJump(float jumpMag);
        //���[�W�����v
        void LowJump(float jumpMag);
        //�W�����v�A�N�V����
        void JumpAction();
        //�W�����v�A�N�V�����̓��͔���
        void JudgeJumpAction();
        //�X�s�[�h�̏����������
        void AdjustSpeed();
        //�X�s�[�h�A�b�v����
        void SpeedUp(float upSpeedValue);
        //�W�����v�~�X�̃X�s�[�h�_�E������
        void JumpMissSpeedDown();
        //�p���X�s�[�h�_�E������
        void GroundWaveSpeedDown();
        //���G���ԏ���
        void Invincible();
        //�X�s�[�h�ˑ��̃X�R�A�{���v�Z����
        void SpeedScoreMagnification();
        //�A�j���[�V����������
        void InitAnimation();
        //�ҋ@�A�j���[�V����
        void WaitingAnimation();
        //���؃A�j���[�V����
        void JumpStartAnimation();
        //���n�A�j���[�V����
        void JumpFinishAnimation();
        //�؋�A�j���[�V����
        void JumpActionXAnimation();
        //�W�����v�A�N�V�����A�j���[�V����(Y��)
        void JumpActionYAnimation();
        //�W�����v�A�N�V�����A�j���[�V����(Z��)
        void JumpActionZAnimation();
        //�W�����v���̑؋�A�N�V����
        void FlightAction();
        //�X�y�V�����W�����v
        void SpecialJump();

		//SE��炷����
		void ActiveSE(wstring se);
		//�W�����v�̃G�t�F�N�g��SE���Đ�
		void JumpEffect(EN_EffectName effectName, wstring seName);
		//�W�����v�A�N�V�����̃G�t�F�N�g��SE���Đ�
		void JumpAcionEffect(EN_EffectName effectName, wstring seName, int animTime);
		//�X�y�V�����W�����v�t���O�𗧂Ă�
		void SetUpSpecialJumpFlag();
		//�G�t�F�N�g��Ǐ]������
		void FollowEffect();
    };

}
//end basecross

