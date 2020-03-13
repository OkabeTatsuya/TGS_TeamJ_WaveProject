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
        //��]�Œ�p��Vec3
        Vec3 m_initRotation;
        //Y���W�ȊO�̌Œ�pVec�R
        Vec3 m_initPosition;
        //�����W�����v�̏㏸��
        float m_highJumpMoveY = 8;
        //�Ⴂ�W�����v�̏㏸��
        float m_lowJumpMoveY = 5;
        //�ړ����x���
        float m_maxSpeed = 5;
        //�ړ����x����
        float m_minSpeed = 2;
        //���݂̈ړ����x
        float m_currentSpeed = (m_maxSpeed-m_minSpeed)/3+m_minSpeed;

        //�󒆃A�N�V�����̃t���O
        bool m_isJumpAction;
        //�󒆃A�N�V�����̏㉺���E�F���t���O
        bool m_isTopJumpAction;
        bool m_isBottomJumpAction;
        bool m_isLeftJumpAction;
        bool m_isRightJumpAction;
        //�󒆃A�N�V�����̓��͎���
        float m_jumpActionLimitTime;
        //���݂̋󒆃A�N�V�����̓��͂ɂ������Ă��鎞��
        float m_currentJumpActionTime;
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
        //�����W�����v
        void HighJump();
        //�Ⴂ�W�����v
        void LowJump();
        //���݂̈ړ����x�̃Q�b�^�[
        float GetCurrentSpeed() {
            return m_currentSpeed;
        }
    };

}
//end basecross

