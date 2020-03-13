/*!
@file Character.h
@brief �����Ă���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Wave : public ObjectBase {
    protected:
        //�ړ����x
        float m_moveSpeed;
        //�ړ�����
        bool m_isMove;
        //��ʊO����̂����W
        float m_offScreenX;
    public:
        Wave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;

        //�ړ�����
        void Move();
        //�ړ�����̃Q�b�^�[
        bool GetIsMove();
        //�ړ�����̃Z�b�^�[
        void SetIsMove(bool move);
        //��ʊO����
        void OffScreen();
    };
}
//end basecross
