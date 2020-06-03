/*!
@file AnimationUI.h
@brief �X�R�AUI
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
		//����������l
		Vec2 StartPos;
		Vec3 StartRot;
		Vec3 StartSca;

		//�ŏI�l
		Vec2 EndPos;
		Vec3 EndRot;
		Vec3 EndSca;

		//�`�悷�郌�C���[
		float LayerNum;
		//�����n�߂鎞��
		float StartTime;
		//�����I��鎞��
		float EndTime;
		//�A�j���[�V�������I��������̓���
		AnimType En_AnimType;
	};

	class AnimationUI : public UIBase {
		St_AnimUI m_st_animUI;
		
		float m_nowTime;

		//�A�j���[�V�����^�C�v�ɉ������A�N�V�����������鎞��
		float m_typeActionTime;
		//�Đ�����SE
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

		//�Z�b�^�[
		void SetIsStartAnim(bool set) { m_isStartAnim = set; };
		void SetIsEndAnim(bool set) { m_isEndAnim = set; };

		//�Q�b�^�[
		bool GetIsStartAnim() { return m_isStartAnim; };
		bool GetIsEndAnim() { return m_isEndAnim; };

		//�֐�
		void ConfirmTime();

		void MovePos();

		void MoveRot();

		void MoveSca();

		void TypeAction();

		void PlaySE();
	};
}
//end basecross
