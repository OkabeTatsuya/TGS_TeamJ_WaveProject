/*!
@file SpriteBase.h
@brief �����X�v���C�g�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Fade : public UIBase {
        //�t�F�[�h�A�E�g���t�F�[�h�C�����̃t���O
        bool m_isFadeOut;
        //�t�F�[�h�ɂ����鎞��
        float m_maxFadeTime;
        //���݃t�F�[�h�ɂ������Ă��鎞��
        float m_currentFadeTime;
    public:
        Fade(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            bool isfadeOut);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        void FadeOut();
        void FadeIn();
    };
}