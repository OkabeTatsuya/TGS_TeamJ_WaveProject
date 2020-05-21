/*!
@file SpriteBase.cpp
@brief 動くスプライト生成の実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    Fade::Fade(const shared_ptr<Stage>& stage,
        wstring nextStageKey) :


        UIBase(stage, Vec3(0.0f),
            Vec3(1400, 800, 0),
            Vec2(0.0f),
            float(11.0f),
            L"FadeBG.png"),
        m_nextStageKey(nextStageKey)
    {
        m_currentFadeTime = 0.0f;
        m_maxFadeTime = 1.0f;
        m_isFadeOut = true;
    }

    Fade::Fade(const shared_ptr<Stage>& stage
    ) :
        UIBase(stage, Vec3(0.0f),
            Vec3(1400, 800, 0),
            Vec2(0.0f),
            float(11.0f),
            L"FadeBG.png") 
    {
        m_currentFadeTime = 0.0f;
        m_maxFadeTime = 1.0f;
        m_isFadeOut = false;
    }


    void Fade::OnCreate() {
        DrawingImage();
        InitializeTransfrom();
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

		auto SE = App::GetApp()->GetXAudio2Manager();
		m_SE = SE->Start(L"Wave.wav", 0.0f, 0.3f);
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
            else {
				auto SE = App::GetApp()->GetXAudio2Manager();
				 SE->Stop(m_SE);
				GetStage()->PostEvent(0.0f, GetStage()->GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), m_nextStageKey);
            }
            
        }
    }
}