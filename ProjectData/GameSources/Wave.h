/*!
@file Wave.h
@brief 動いてくる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum WaveType {
		en_waveS,
		en_waveM,
		en_waveL
	};

    class Wave : public MoveSpriteBase {
    protected:
		//波のタイプ
		WaveType m_waveType;
        //移動判定
        bool m_isMove;
        //画面外判定のｘ座標
        float m_offScreenX;
		//張り付けるテクスチャ
		wstring m_textureName;
    public:
        Wave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position,
			int&  layer,
			wstring tex);

        virtual void OnUpdate() override;
        virtual void OnCreate() override;

		//コリジョンの作成
		void CreateCollision();
        //移動処理
        void Move();
        //移動判定のゲッター
        bool GetIsMove();
        //移動判定のセッター
        void SetIsMove(bool move);
        //画面外判定
        void OffScreen();
    };
}
//end basecross
