/*!
@file SpriteBase.h
@brief 動くスプライト生成クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Fade : public UIBase {
        //フェードアウトかフェードインかのフラグ
        bool m_isFadeOut;
        //フェードにかける時間
        float m_maxFadeTime;
        //現在フェードにかかっている時間
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