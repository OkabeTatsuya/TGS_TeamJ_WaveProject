/*!
@file SpriteBase.h
@brief “®‚­ƒXƒvƒ‰ƒCƒg¶¬ƒNƒ‰ƒX
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Fade : public UIBase {
        //ƒtƒF[ƒhƒAƒEƒg‚©ƒtƒF[ƒhƒCƒ“‚©‚Ìƒtƒ‰ƒO
        bool m_isFadeOut;
        //ƒtƒF[ƒh‚É‚©‚¯‚éŠÔ
        float m_maxFadeTime;
        //Œ»İƒtƒF[ƒh‚É‚©‚©‚Á‚Ä‚¢‚éŠÔ
        float m_currentFadeTime;
        //ƒtƒF[ƒhƒAƒEƒg‚Ì‚Ég‚¤Ÿ‚ÌƒXƒe[ƒW‚Ìkey
        wstring m_nextStageKey;
		//ï¿½Äï¿½ï¿½ï¿½ï¿½ï¿½SE
		shared_ptr<SoundItem> m_SE;

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