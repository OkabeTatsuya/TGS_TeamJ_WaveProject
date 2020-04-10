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
        float& layer) :


        UIBase(stage, rotation,
            scale,
            position,
            layer,
            L"FadeBG.png")
    {}


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

    }

    void Fade::OnUpdate() {
        auto drawPtr = GetComponent<PCTSpriteDraw>();
        auto color = drawPtr->GetDiffuse();
        color.w += 1.0f / 0.4f * App::GetApp()->GetElapsedTime();
    }
}