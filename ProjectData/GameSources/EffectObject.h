/*!
@file EffectOject.h
@brief �G�t�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum EffectType {
		en_Jump,
		en_SuperJump,
		en_Move
	};

	class EffectObject : public GameObject{
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_efkEffect;

		//�G�t�F�N�g���Đ�������
		vector<shared_ptr<EfkPlay>> m_efkPlay;

		shared_ptr<EfkInterface> m_efkInterface;

		wstring m_effectName;

		int m_effectNum;

		int m_playEffectCount;

		int m_maxEffectNum;

	public:
		EffectObject(const shared_ptr<Stage>& StagePtr);

		void OnCreate()override;

		void OnUpdate()override;

		//�Q�b�^�[�A�Z�b�^�[
		void SetEfkPlay(shared_ptr<EfkPlay> set, EffectType effectType)
		{ 
			m_efkPlay[effectType] = set;
			GetTypeStage<GameStage>()->SetEfkPlay(m_efkPlay, (int)effectType);
		}

		shared_ptr<EfkPlay> GetEfkPlay(EffectType effectType) { return m_efkPlay[effectType]; }

		void CreateEfkPlay();

		//�Ǐ]���Ȃ��G�t�F�N�g
		void PlayEffect(EN_EffectName effName, EffectType effectType, Vec3 pos);
	};
}