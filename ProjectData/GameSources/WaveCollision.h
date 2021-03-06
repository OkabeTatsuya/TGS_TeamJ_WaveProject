/*!
@file Character.h
@brief 動く波の当たり判定
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class WaveCollision : public ObjectBase {
    private:
        wstring m_typeName;
    public:
        WaveCollision(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position,
            wstring typeName
            );

		virtual void OnCreate() override;
        virtual void OnUpdate() override;
        void Stop();

		//波が生成されたときコリジョンを起こす
        void AwakeCollision();
	};
}
//end basecross
