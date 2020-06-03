/*!
@file AnimationUI.h
@brief スコアUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum AnimType {
		Loop,
		Delete,
		Stay
	};

	struct St_AnimUI {
		//初期化する値
		Vec2 StartPos;
		Vec3 StartRot;
		Vec3 StartSca;

		//最終値
		Vec2 EndPos;
		Vec3 EndRot;
		Vec3 EndSca;

		//描画するレイヤー
		float LayerNum;
		//動き始める時間
		float StartTime;
		//動き終わる時間
		float EndTime;
		//アニメーションが終わった時の動き
		AnimType En_AnimType;
	};

	class AnimationUI : public UIBase {
		St_AnimUI m_st_animUI;
		
		float m_nowTime;

		//アニメーションタイプに応じたアクションをさせる時間
		float m_typeActionTime;
		//再生するSE
		wstring m_SEName;
		shared_ptr<SoundItem> m_SE;
		bool m_isPlaySE;

		bool m_isStartAnim;
		bool m_isEndAnim;

	public:
		AnimationUI(const shared_ptr<Stage>& stage,
			St_AnimUI& animUI_state,
			wstring tex);

		AnimationUI(const shared_ptr<Stage>& stage,
			St_AnimUI& animUI_state,
			wstring tex, wstring seName);

		AnimationUI(const shared_ptr<Stage>& stage,
			St_AnimUI& animUI_state,
			wstring tex, float typeActionTime);

		AnimationUI(const shared_ptr<Stage>& stage,
			St_AnimUI& animUI_state,
			wstring tex, float typeActionTime, wstring seName);

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		virtual void OnDestroy() override;

		//セッター
		void SetIsStartAnim(bool set) { m_isStartAnim = set; };
		void SetIsEndAnim(bool set) { m_isEndAnim = set; };

		//ゲッター
		bool GetIsStartAnim() { return m_isStartAnim; };
		bool GetIsEndAnim() { return m_isEndAnim; };

		//関数
		void ConfirmTime();

		void MovePos();

		void MoveRot();

		void MoveSca();

		void TypeAction();

		void PlaySE();
	};
}
//end basecross
