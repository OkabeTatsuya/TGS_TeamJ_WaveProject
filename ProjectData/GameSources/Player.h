/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
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
        //SE��炷����
        void ActiveSE(wstring se);
    };

}
//end basecross

