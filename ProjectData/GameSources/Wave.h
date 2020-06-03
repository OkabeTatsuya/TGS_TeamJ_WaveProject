/*!
@file Wave.h
@brief �����Ă���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum WaveType {
		en_waveS,
		en_waveM,
		en_waveL
	};

    class Wave : public MoveSpriteBase {
    protected:
		//�g�̃^�C�v
		WaveType m_waveType;
        //�ړ�����
        bool m_isMove;
        //��ʊO����̂����W
        float m_offScreenX;
		//����t����e�N�X�`��
		wstring m_textureName;
    public:
        Wave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position,
			int&  layer,
			wstring tex);

        virtual void OnUpdate() override;
        virtual void OnCreate() override;

		//�R���W�����̍쐬
		void CreateCollision();
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
