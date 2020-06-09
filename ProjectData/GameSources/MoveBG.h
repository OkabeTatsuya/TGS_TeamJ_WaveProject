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

		Vec2 m_imageSize;
		wstring m_texture;
		vector<float> m_coordinate;

	public:
		MoveBG(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& position,
			Vec2& image,
			int&  layer,
			wstring tex,
			float offScreenX,
			float moveSpeed);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;

		//�ړ�����
		void Move();
		//UV���g�����ړ�����
		void MoveTexture();

		//�ړ�����̃Q�b�^�[
		bool GetIsMove();
		//�ړ�����̃Z�b�^�[
		void SetIsMove(bool move);
		//��ʊO����
		void OffScreen();
	};

}
//end basecross
