/*!
@file SpriteBase.cpp
@brief 動くスプライト生成の実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    Fade::Fade(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec2& position,
        float& layer,
        bool isfadeOut) :


        UIBase(stage, rotation,
            scale,
            position,
            layer,
            L"FadeBG.png"),
        m_isFadeOut(isfadeOut)
    {
        m_currentFadeTime = 0;
        m_maxFadeTime = 1.0f;
    }


    void Fade::OnCreate() {
        DrawingImage();
        Col4 color(1, 1, 1, 1);
        Vec2 tipSize = Vec2(1.0f, 1.0f);

        float halfSize = 0.5f;
        vector<VertexPositionColorTexture> vertices = {
            {VertexPositionColorTexture(Vec3(-halfSize,halfSize,0),color,Vec2(0.0f,0.0f))},
            {VertexPositionColorTexture(Vec3(halfSize,halfSize,0),color,Vec2(0.1f,0.0f))},
            {VertexPositionColorTexture(Vec3(-halfSize,-halfSize,0),color,Vec2(0.0f,1.0f))},
            {VertexPositionColorTexture(Vec3(halfSize,-halfSize,0),color,Vec2(0.1f,1.0f))}
        };


        // テクスチャの貼り付け
        auto drawPtr = GetComponent<PCTSpriteDraw>();
        drawPtr->UpdateVertices(vertices);
        if (m_isFadeOut) {
            auto colors = drawPtr->GetDiffuse();
            colors.w = 0.0f;
            drawPtr->SetDiffuse(colors);
        }
    }

    void Fade::FadeIn() {
        auto drawPtr = GetComponent<PCTSpriteDraw>();
        auto color = drawPtr->GetDiffuse();
        color.w -= 1.0f / m_maxFadeTime * App::GetApp()->GetElapsedTime();
        drawPtr->SetDiffuse(color);
    }

    void Fade::FadeOut() {
        auto drawPtr = GetComponent<PCTSpriteDraw>();
        auto color = drawPtr->GetDiffuse();
        color.w += 1.0f / m_maxFadeTime * App::GetApp()->GetElapsedTime();
        drawPtr->SetDiffuse(color);
    }

    void Fade::OnUpdate() {
        m_currentFadeTime += App::GetApp()->GetElapsedTime();
        if (m_isFadeOut) {
            FadeOut();
        }
        else {
            FadeIn();
        }

        if (m_currentFadeTime >= m_maxFadeTime) {
            if (!m_isFadeOut) {
                GetStage()->RemoveGameObject<Fade>(GetThis<Fade>());
            }
            
        }
    }
}