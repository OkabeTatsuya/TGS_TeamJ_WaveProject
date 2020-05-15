/*!
@file EffectObject.cpp
@brief エフェクトの実態
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

	/*追従しないエフェクト
		effName エフェクトの名前
		pos		初期座標
	*/
	void EffectObject::PlayEffect(EN_EffectName effName, EffectType effectType, Vec3 pos) {
		auto efk = GetTypeStage<GameStage>()->GetEfkEffect();

		m_efkPlay[effectType] = ObjectFactory::Create<EfkPlay>(efk[effName], pos);
		 m_efkPlay[effectType]->SetScale(Vec3(0.08f,0.08f,1.0f));
		 m_efkPlay[effectType]->SetSpeed(0.8f);
		 GetTypeStage<GameStage>()->SetEfkPlay(m_efkPlay, 0);
	}

	/*追従しないエフェクト
		effName エフェクトの名前
		pos		初期座標
	*/
	//追従するエフェクト
	void EffectObject::PlayEffect(shared_ptr<GameObject> obj) {
		//if (m_playEffectCount < m_efkPlay.size()) {
		//	Vec3 objPos = obj->GetComponent<Transform>()->GetPosition();
		//	m_efkPlay[m_playEffectCount] = ObjectFactory::Create<EfkPlay>(m_efkEffect, objPos);
		//}
		//else {
		//	m_playEffectCount = 0;
		//}
	}

}