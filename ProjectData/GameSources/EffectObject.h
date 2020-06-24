/*!
@file EffectOject.h
@brief エフェクト
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
		//エフェクト
		shared_ptr<EfkEffect> m_efkEffect;

		//エフェクトを再生させる
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

		//ゲッター、セッター
		void SetEfkPlay(shared_ptr<EfkPlay> set, EffectType effectType)
		{ 
			m_efkPlay[effectType] = set;
			GetTypeStage<GameStage>()->SetEfkPlay(m_efkPlay, (int)effectType);
		}

		shared_ptr<EfkPlay> GetEfkPlay(EffectType effectType) { return m_efkPlay[effectType]; }

		void CreateEfkPlay();

		//追従しないエフェクト
		void PlayEffect(EN_EffectName effName, EffectType effectType, Vec3 pos);
	};
}