/*!
@file Wave.cpp
@brief 動く波の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    Wave::Wave(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position,
		int&  layer,
		wstring tex) :

        MoveSpriteBase(stage,
            rotation, scale, position, layer
        )
    {
		m_textureName = tex;
        m_isMove = true;
        m_offScreenX = -7;
    }

    void Wave::OnCreate() {
        DrawingImage(m_textureName);
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

		CreateCollision();
        //SetTexture(L"");
    }

    void Wave::OnUpdate() {
        Move();
        OffScreen();
    }

    //画面外判定
    void Wave::OffScreen() {
        if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
            SetIsMove(false);
        }
    }

	//
	void Wave::CreateCollision() {
		shared_ptr<WaveCollision> waveCol;

		switch (m_waveType)
		{
		case WaveType::en_waveS:
			waveCol = GetStage()->AddGameObject<WaveCollision>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(m_position.x - 1, -3.0f, -7.0f));
			waveCol->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
			break;
		case WaveType::en_waveM:
			waveCol = GetStage()->AddGameObject<WaveCollision>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(m_position.x - 1, -3.0f, -7.0f));
			waveCol->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
			break;
		case WaveType::en_waveL:
			waveCol = GetStage()->AddGameObject<WaveCollision>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(m_position.x - 1, -3.0f, -7.0f));
			waveCol->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
			break;
		default:
			break;
		}
	};

    //移動処理
    void Wave::Move() {
        if (m_isMove) {
            Movement(GetComponent<Transform>());
        }
    }

    //移動判定のゲッター
    bool Wave::GetIsMove() {
        return m_isMove;
    }

    //移動判定のセッター
    void Wave::SetIsMove(bool move) {
        m_isMove = move;
    }
}
//end basecross
