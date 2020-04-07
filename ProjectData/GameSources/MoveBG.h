/*!
@file MoveBG.h
@brief �����Ă���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveBG : public MoveSpriteBase {
	protected:
		//�ړ�����
		bool m_isMove;
		//��ʊO����̂����W
		float m_offScreenX;

		wstring m_texture;
	public:
		MoveBG(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			wstring tex,
			float offScreenX);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;

		//�ړ�����
		void Move();

		//
		//void Movement(shared_ptr<Transform> transPtr);

		//�ړ�����̃Q�b�^�[
		bool GetIsMove();
		//�ړ�����̃Z�b�^�[
		void SetIsMove(bool move);
		//��ʊO����
		void OffScreen();
	};

}
//end basecross
