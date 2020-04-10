/*!
@file AnimationUI.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	AnimationUI::AnimationUI(const shared_ptr<Stage>& stage,
		St_AnimUI& animUI_state,
		wstring tex) :
		UIBase(stage,
			animUI_state.StartRot,
			animUI_state.StartSca,
			animUI_state.StartPos,
			animUI_state.LayerNum,
			tex),
		m_st_animUI(animUI_state)
	{
		m_nowTime = 0.0f;

		m_isStartAnim = true;
		m_isEndAnim = false;

		m_typeActionTime = 0;
	}

	AnimationUI::AnimationUI(const shared_ptr<Stage>& stage,
		St_AnimUI& animUI_state,
		wstring tex, float typeActionTime) :
		UIBase(stage,
			animUI_state.StartRot,
			animUI_state.StartSca,
			animUI_state.StartPos,
			animUI_state.LayerNum,
			tex),
		m_st_animUI(animUI_state),
		m_typeActionTime(typeActionTime)
	{
		m_nowTime = 0.0f;

		//m_isStartAnim = true;
		m_isEndAnim = false;

	}


	void AnimationUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
	}

	void AnimationUI::OnUpdate() {
		ConfirmTime();
		MovePos();
	}

	void AnimationUI::ConfirmTime() {
		//
		if (m_typeActionTime > m_nowTime) {
			auto delta = App::GetApp()->GetElapsedTime();
			m_nowTime += delta;
		}
		else if(m_isEndAnim){
			TypeAction();
		}

		//アニメーションをスタートさせる
		if (m_st_animUI.StartTime < m_nowTime) {
			m_isStartAnim = true;
		}

		//アニメーションを止める
		if (m_st_animUI.EndTime < m_nowTime) {
			auto a = GetComponent<Transform>()->GetPosition();
			GetComponent<Transform>()->SetPosition(m_st_animUI.EndPos.x, m_st_animUI.EndPos.y,0.0f);
			m_isEndAnim = true;
		}
	}

	void AnimationUI::MovePos() {
		if (m_st_animUI.EndTime > m_nowTime && m_isStartAnim)
		{
			auto nowPos = GetComponent<Transform>()->GetPosition();

			auto moveVecX = m_st_animUI.EndPos.x - m_st_animUI.StartPos.x;
			auto moveVecY = m_st_animUI.EndPos.y - m_st_animUI.StartPos.y;

			auto moveVec = moveVecX * moveVecX + moveVecY * moveVecY;
			auto nowVec = nowPos.x * nowPos.x + nowPos.y * nowPos.y;

			auto time = App::GetApp()->GetElapsedTime();
			auto moveDelta = Vec2(moveVecX, moveVecY) / (m_st_animUI.EndTime - m_st_animUI.StartTime);

			//if (nowVec < moveVec)
			{
				auto movePos = nowPos + Vec3(moveDelta.x * time, moveDelta.y * time, 0.0f);
				GetComponent<Transform>()->SetPosition(movePos);
			}
		}
	}

	void AnimationUI::MoveSca() {

	}

	void AnimationUI::MoveRot() {

	}

	void AnimationUI::TypeAction() {
		if (m_isEndAnim == AnimType::Delete) {
			GetStage()->RemoveGameObject<AnimationUI>(GetThis<AnimationUI>());
		}
	}


}