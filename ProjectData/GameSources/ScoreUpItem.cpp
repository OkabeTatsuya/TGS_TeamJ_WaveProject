/*!
@file ScoreUpItem.cpp
@brief 動く波の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ScoreUpItem::ScoreUpItem(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& position,
		Vec2 texSize,
		int&  layer
	) :

		MoveSpriteBase(stage,
			rotation, Vec3(0.3f,0.3f,1.0f), position, layer
		)
	{
		m_isMove = true;
		m_offScreenX = -6;
		m_texSize = texSize;
	}

	void ScoreUpItem::OnCreate() {
		DrawingImage(L"Coin.png", m_texSize);
		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetScale(m_scale);
		transPtr->SetRotation(m_rotation);

		auto collision = AddComponent<CollisionObb>();
		collision->SetAfterCollision(AfterCollision::None);
		//SetTexture(L"");
	}

	void ScoreUpItem::OnUpdate() {
		Move();
		OffScreen();
	}

	void ScoreUpItem::OnDestroy() {

	}

	void ScoreUpItem::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			auto &gameManager = GameManager::GetInstance();
			gameManager.AddItemScore();

			auto collision = GetComponent<CollisionObb>();
			collision->SetUpdateActive(false);
			auto drawPtr = GetComponent<PCTStaticDraw>();
			drawPtr->SetDrawActive(false);
			PlaySE();
		}
	}

	//画面外判定
	void ScoreUpItem::OffScreen() {
		if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
			SetIsMove(false);
		}
	}

	//移動処理
	void ScoreUpItem::Move() {
		if (m_isMove) {
			Movement(GetComponent<Transform>());
		}
	}

	//移動判定のゲッター
	bool ScoreUpItem::GetIsMove() {
		return m_isMove;
	}

	//移動判定のセッター
	void ScoreUpItem::SetIsMove(bool move) {
		m_isMove = move;
		m_isGetItem = false;
		VisibleItem();
	}

	void ScoreUpItem::VisibleItem() {
		if (!m_isGetItem) {
			auto collision = GetComponent<CollisionObb>();
			collision->SetUpdateActive(true);
			auto drawPtr = GetComponent<PCTStaticDraw>();
			drawPtr->SetDrawActive(true);
		}
	}

	void ScoreUpItem::PlaySE() {
		auto audioManager = App::GetApp()->GetXAudio2Manager();
		m_SE = audioManager->Start(L"decision28.wav",0, 0.6f);
	};


}
//end basecross
