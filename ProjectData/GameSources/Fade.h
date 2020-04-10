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
        //フェードアウトの時に使う次のステージのkey
        wstring m_nextStageKey;
    public:
        Fade(const shared_ptr<Stage>& stage,
            wstring nextStageKey);
        Fade(const shared_ptr<Stage>& stage);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
        void FadeOut();
        void FadeIn();
    };
}