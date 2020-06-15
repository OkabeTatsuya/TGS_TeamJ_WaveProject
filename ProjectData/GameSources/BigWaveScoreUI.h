/*!
@file BigWaveScoreUI.h
@brief ビッグウェーブで獲得したスコアを表示するUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BigWaveScoreUI : public ImageUI {
		vector<shared_ptr<SoundItem>> m_SE;
		shared_ptr<ScoreUIPanel> m_scoreUI;
		shared_ptr<PCTSpriteDraw> m_drawPtr;

		bool m_isAnimUI;
		bool m_isPlaySE;
		float m_animSpeed;
		float m_animTimer;
		float m_animEndTime;
	public:
		BigWaveScoreUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		virtual void OnDestroy() override;

		void AnimUI();

		void PlaySE();

		void ResetState();
	};
}
//end basecross
