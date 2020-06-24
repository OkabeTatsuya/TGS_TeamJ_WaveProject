/*!
@file EffectObject.cpp
@brief �G�t�F�N�g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	EffectObject::EffectObject(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr) {
		m_maxEffectNum = 3;
	}

	void EffectObject::OnCreate() {
		m_efkInterface = ObjectFactory::Create<EfkInterface>();

		auto trans = AddComponent<Transform>();
		trans->SetPosition(Vec3(0.0f,0.0f, -15.0f));
		trans->SetScale(Vec3(1.0f));
		trans->SetRotation(Vec3(0.0f));
		CreateEfkPlay();
	}

	void EffectObject::OnUpdate() {
	}

	void EffectObject::CreateEfkPlay() {
		auto efk = GetTypeStage<GameStage>()->GetEfkEffect();
		for (int i = 0; i < m_maxEffectNum; i++) {
			m_efkPlay.push_back(NULL);
		}
	}

	/*�Ǐ]���Ȃ��G�t�F�N�g
		effName �G�t�F�N�g�̖��O
		pos		�������W
	*/
	void EffectObject::PlayEffect(EN_EffectName effName, EffectType effectType, Vec3 pos) {
		auto efk = GetTypeStage<GameStage>()->GetEfkEffect();

		m_efkPlay[effectType] = ObjectFactory::Create<EfkPlay>(efk[effName], pos);
		 m_efkPlay[effectType]->SetScale(Vec3(0.08f,0.08f,1.0f));
		 m_efkPlay[effectType]->SetSpeed(0.8f);
		 GetTypeStage<GameStage>()->SetEfkPlay(m_efkPlay, 0);
	}
}