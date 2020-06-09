/*!
@file UnlockStageUI.h
@brief ÉXÉRÉAUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UnlockStageUI : public ImageUI {
		//UI
		shared_ptr<ImageUI> m_lockUI;
		shared_ptr<ImageUI> m_stageImageUI;
		shared_ptr<ImageUI> m_stageNumUI;
		shared_ptr<ImageUI> m_pushButtonUI;
		shared_ptr<ImageUI> m_UnlockBackUI;

		//SE
		vector<shared_ptr<SoundItem>> m_SE;
		vector <bool> m_isPlaySE;
		//
		vector<wstring> m_stageImageName;
		vector<wstring> m_stageNumImageName;

		bool m_isPlayAnim;
		bool m_isEndAnim;
		bool m_isVisibleUI;
		float m_animSpeed;
		float m_animTimer;
		float m_animEndTime;

		vector<float> m_nextAnimeTime;

	public:
		UnlockStageUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		virtual void OnDestroy() override;

		bool GetIsEndAnim() { return m_isEndAnim; };

		void CreateUI();

		void UnLockAnim();

		void AnimUI();

		void PlayAnim();

		void PlaySE(int seNum, wstring seName, float seVol);
	};
}
//end basecross
