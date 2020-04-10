/*!
@file Character.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    ScoreUI::ScoreUI(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec2& position,
        float& layer,
        wstring tex) :

        UIBase(stage,rotation,
            scale,
            position,
            layer,
            tex)
    {}

    void ScoreUI::OnCreate() {
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

    }

    void ScoreUI::SetNumber(int number) {
        number += 1;
        Col4 color(1, 1, 1, 1);
        Vec2 tipSize = Vec2(1.0f, 1.0f);

        float halfSize = 0.5f;
        vector<VertexPositionColorTexture> vertices = {
            {VertexPositionColorTexture(Vec3(-halfSize,halfSize,0),color,Vec2(0.1f * number -0.1f,0.0f))},
            {VertexPositionColorTexture(Vec3(halfSize,halfSize,0),color,Vec2(0.1f * number,0.0f))},
            {VertexPositionColorTexture(Vec3(-halfSize,-halfSize,0),color,Vec2(0.1f * number -0.1f,1.0f))},
            {VertexPositionColorTexture(Vec3(halfSize,-halfSize,0),color,Vec2(0.1f * number,1.0f))}
        };


        // テクスチャの貼り付け
        auto drawPtr = GetComponent<PCTSpriteDraw>();
        drawPtr->UpdateVertices(vertices);
    }

}
//end basecross
