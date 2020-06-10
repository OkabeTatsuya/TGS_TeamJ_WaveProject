/*!
@file ScoreUpItem.h
@brief �����Ă���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ScoreUpItem : public MoveSpriteBase {
	protected:
		//�ړ�����
		bool m_isMove;
		//�A�C�e���擾����
		bool m_isGetItem;
		//��ʊO����̂����W
		float m_offScreenX;

		Vec2 m_texSize;

		shared_ptr<SoundItem> m_SE;

	public:
		ScoreUpItem(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& position,
			Vec2 texSize,
			int&  layer
			);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		//�ړ�����
		void Move();
		//�ړ�����̃Q�b�^�[
		bool GetIsMove();
		//�ړ�����̃Z�b�^�[
		void SetIsMove(bool move);
		//��ʊO����
		void OffScreen();

		void VisibleItem();

		void PassiveCollision();

		void PlaySE();
	};
}
//end basecross
