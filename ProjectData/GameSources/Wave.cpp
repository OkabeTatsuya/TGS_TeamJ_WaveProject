/*!
@file Wave.cpp
@brief �����g�̎���
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

        auto waveCol = GetStage()->AddGameObject<WaveCollision>(Vec3(0, 0, 0), Vec3(0.1, 0.1, 1), Vec3(m_position.x - 0.5f, m_position.y-0.5, -7.0f));
        waveCol->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
        //SetTexture(L"");
    }

    void Wave::OnUpdate() {
        Move();
        OffScreen();
    }

    //��ʊO����
    void Wave::OffScreen() {
        if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
            SetIsMove(false);
        }
    }

    //�ړ�����
    void Wave::Move() {
        if (m_isMove) {
            Movement(GetComponent<Transform>());
        }
    }

    //�ړ�����̃Q�b�^�[
    bool Wave::GetIsMove() {
        return m_isMove;
    }

    //�ړ�����̃Z�b�^�[
    void Wave::SetIsMove(bool move) {
        m_isMove = move;
    }
}
//end basecross
