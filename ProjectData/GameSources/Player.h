/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
    class Player : public ObjectBase {
    protected:
        //�W�����v�̃t���O
        bool m_isJump = true;
        //�n�C�W�����v�̏㏸��
        float m_highJumpMoveY;
        //���[�W�����v�̏㏸��
        float m_lowJumpMoveY;
        //�ړ����x���
        float m_maxSpeed;
        //�ړ����x����
        float m_minSpeed;
        //���݂̈ړ����x
        float m_currentSpeed;
        //�p���X�s�[�h�_�E���̌�����
        float m_groundWaveDownSpeedValue;
        //���݂̃W�����v�̃O���[�h����b��
        float m_currentJumpGradeTime;
        //�M���M���ŃW�����v�������̃X�s�[�h�̏㏸�ʔ{��
        float m_jumpGradeMagnification;
        //�W�����v�O���[�h����̓�Փx
        float m_jumpGradeTime;

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
    private:
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
        void HighJump();
        //���[�W�����v
        void LowJump();
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
        //���݂̈ړ����x�̃Q�b�^�[
        float GetCurrentSpeed() {
            return m_currentSpeed;
        }
    };

}
//end basecross

