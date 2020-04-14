/*!
@file GoalObject.h
@brief �Q�[���N���A����I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GoalObject : public MoveSpriteBase {
	protected:
		//�ړ�����
		bool m_isMove;
		float m_offsetPosX;
		wstring m_textureName;

	public:
		GoalObject(const shared_ptr<Stage>& StagePtr,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			wstring tex);

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		//�Q�b�^�[�ƃZ�b�^�[
		//�ړ�����̃Q�b�^�[
		bool GetIsMove() { return m_isMove; }
		//�ړ�����̃Z�b�^�[
		void SetIsMove(bool move) { m_isMove = false; };

		//�֐�
		//�I�u�W�F�N�g�𓮂����A�I�t�Z�b�g�𒴂�����~�߂�
		void MoveObject();

	};

}